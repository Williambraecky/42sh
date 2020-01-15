/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 00:51:21 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 00:41:17 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	mark_process_status(t_cmd *cmd, pid_t pid, int status)
{
	t_proc	*curr;

	if (pid == 0)
		return (-1); //Nothing returned from wait
	else if (pid < 0)
		return (-1); //wait error
	curr = cmd->pipeline;
	while (curr)
	{
		if (curr->pid == pid)
		{
			curr->status = status;
			if (WIFSTOPPED(status))
				curr->stopped = 1;
			else
				curr->completed = 1;
			return (0);
		}
		curr = curr->next;
	}
	return (-1); //no job found with pid
}

void		job_wait(t_sh *shell, t_cmd *cmd)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-cmd->pgid, &status, WUNTRACED);
	while (!mark_process_status(cmd, pid, status) &&
		!job_is_completed(cmd) &&
		!job_is_stopped(cmd))
	{
		pid = waitpid(-cmd->pgid, &status, WUNTRACED);
	}
	if (WIFEXITED(status))
		set_last_return_code(shell, WEXITSTATUS(status));
	else if (WIFSTOPPED(status))
	{
		set_last_return_code(shell, WSTOPSIG(status) + 128);
		cmd->background = 1; // TODO: add cmd to job control
	}
	else if (WIFSIGNALED(status))
		set_last_return_code(shell, WTERMSIG(status) + 128);
	else
		set_last_return_code(shell, 1);
}
