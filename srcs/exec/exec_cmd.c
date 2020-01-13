/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:43:46 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 18:02:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
** TODO: validate that cmd_is_empty is good
*/

int			exec_cmd(t_sh *shell, t_cmd *cmd)
{
	if (cmd_is_empty(cmd))
		return (SH_SUCCESS);
	exec_pipeline(shell, cmd->pipeline);
	if (cmd->background)
		jobs_to_background(shell, cmd, 0);
	else
		jobs_to_foreground(shell, cmd, 0);
	return (SH_SUCCESS);
}
