/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:43:46 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/16 02:34:33 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** TODO: some errors are not critical (i. e open errors)
*/

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
			pipeline->io.pipe_close = pipe_[0];
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
	int		ret;

	if (cmd_is_empty(cmd))
	{
		free_cmd(cmd);
		return (SH_SUCCESS);
	}
	if (cmd_make_string(cmd) != SH_SUCCESS)
	{
		free_cmd(cmd);
		return (SH_ERR_MALLOC);
	}
	ret = exec_pipeline(shell, cmd->pipeline);
	if (ret != SH_SUCCESS)
	{
		free_cmd(cmd);
		set_last_return_code(shell, 1);
		return (ret);
	}
	if (cmd->background)
	{
		jobs_to_background(shell, cmd, 0);
		set_last_return_code(shell, ret);
	}
	else
		jobs_to_foreground(shell, cmd, 0);
	return (SH_SUCCESS);
}
