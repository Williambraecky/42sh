/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 00:51:21 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 18:02:14 by wbraeckm         ###   ########.fr       */
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
			{
				curr->completed = 1;
				if (WIFSIGNALED(status))
					; //TODO: handle error message here
			}
			return (0);
		}
		curr = curr->next;
	}
	return (-1); //no job found with pid
}

void		job_wait(t_cmd *cmd)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!mark_process_status(cmd, pid, status) &&
		!job_is_completed(cmd) &&
		!job_is_stopped(cmd))
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	}
	//TODO: should we change the last return code here? using status
}
