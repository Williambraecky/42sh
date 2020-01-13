/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:43:46 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 01:28:12 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	exec_pipeline(t_sh *shell, t_proc *pipeline)
{
	int	pipe_[2];
	int	ret;

	ret = SH_SUCCESS;
	while (pipeline)
	{
		if (pipeline->next)
		{
			pipe(pipe_);
			pipeline->io.out = pipe_[1];
			pipeline->next->io.in = pipe_[0];
		}
		if ((ret = exec_proc(shell, pipeline)) != SH_SUCCESS)
			break ;
		pipeline = pipeline->next;
	}
	return (ret);
}

/*
** NOTE: if cmd->background is set: add to jobs and do not wait for proc
** NOTE: should change the return code here
*/

static int	exec_cmd_bg(t_sh *shell, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (SH_ERR_FORK);
	if (pid != 0)
	{
		cmd->pgid = pid;
		jobs_add(shell, cmd);
		return (SH_SUCCESS);
	}
	exec_pipeline(shell, cmd->pipeline);
	//NOTE: commands in background set the last return code to 0
	return (SH_SUCCESS);
}

/*
** TODO: validate that cmd_is_empty is good
*/

int			exec_cmd(t_sh *shell, t_cmd *cmd)
{
	if (cmd_is_empty(cmd))
		return (SH_SUCCESS);
	if (cmd->background)
		return (exec_cmd_bg(shell, cmd));
	exec_pipeline(shell, cmd->pipeline);
	jobs_to_foreground(shell, cmd, 0);
	return (SH_SUCCESS);
}
