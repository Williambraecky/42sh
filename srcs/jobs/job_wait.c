/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 00:51:21 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/30 23:57:31 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int		mark_process_status(t_cmd *cmd, pid_t pid, int status)
{
	t_proc	*curr;

	if (pid == 0)
		return (-1);
	else if (pid < 0 || !cmd)
		return (-1);
	curr = cmd->pipeline;
	while (curr)
	{
		if (curr->pid == pid)
		{
			curr->status = status;
			ft_strdel(&curr->status_str);
			cmd->notified = 0;
			if (WIFSTOPPED(status))
				curr->stopped = 1;
			else if (WIFSIGNALED(status) || WIFEXITED(status))
				curr->completed = 1;
			return (0);
		}
		curr = curr->next;
	}
	return (-1);
}

static t_cmd	*get_cmd(t_sh *shell, pid_t proc_pid)
{
	size_t	i;
	t_cmd	*curr;
	t_proc	*proc;

	i = 0;
	while (i < shell->jobs.size)
	{
		curr = ft_vecget(&shell->jobs, i++);
		proc = curr->pipeline;
		while (proc)
		{
			if (proc->pid == proc_pid)
				return (curr);
			proc = proc->next;
		}
	}
	return (NULL);
}

/*
** NOTE: updates any backgrounded jobs without blocking
*/

void			jobs_update_status(t_sh *shell)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG | WCONTINUED);
	while (!mark_process_status(get_cmd(shell, pid), pid, status))
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG | WCONTINUED);
	}
}

static void		job_react(t_sh *shell, t_cmd *cmd, int status)
{
	cmd->status = status;
	if (WIFEXITED(status))
		set_exit_code(shell, WEXITSTATUS(status));
	else if (WIFSTOPPED(status))
	{
		ft_printf("\n");
		set_exit_code(shell, WSTOPSIG(status) + 128);
		if (shell->job_control)
		{
			jobs_add(shell, cmd, 0);
			return ;
		}
	}
	else if (WIFSIGNALED(status))
	{
		set_exit_code(shell, WTERMSIG(status) + 128);
		if (WTERMSIG(status) != 2)
			job_notify_cmd(cmd, shell->jobs.size + 1, shell->jobs.size);
	}
	free_cmd(cmd);
}

void			job_wait(t_sh *shell, t_cmd *cmd)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-cmd->pgid, &status, WUNTRACED | WCONTINUED);
	while (!mark_process_status(cmd, pid, status) &&
		!job_is_completed(cmd) &&
		!job_is_stopped(cmd))
	{
		pid = waitpid(-cmd->pgid, &status, WUNTRACED | WCONTINUED);
	}
	status = jobs_last_status(cmd);
	job_react(shell, cmd, status);
}
