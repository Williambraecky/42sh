/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:43:46 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/30 22:59:58 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	can_continue(int ret)
{
	return (ret != SH_ERR_MALLOC && ret != SH_ERR_FORK);
}

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
		if (!can_continue((ret = exec_proc(shell, pipeline))))
			break ;
		if (pipeline->parent->background && pipeline->io.out)
			close(pipeline->io.out);
		if (pipeline->parent->background && pipeline->io.in)
			close(pipeline->io.in);
		pipeline = pipeline->next;
	}
	return (ret);
}

static int	pre_exec(t_cmd *cmd)
{
	if (cmd_make_string(cmd) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

static void	post_exec(t_sh *shell, t_cmd *cmd, int ret)
{
	if (ret != SH_SUCCESS)
	{
		free_cmd(cmd);
		set_exit_code(shell, 1);
		return ;
	}
	if (cmd->background && shell->job_control)
	{
		jobs_to_background(shell, cmd, 0);
		set_exit_code(shell, ret);
	}
	else
		jobs_to_foreground(shell, cmd, 0);
}

int			exec_cmd(t_sh *shell, t_cmd *cmd)
{
	int		ret;

	if (cmd_is_empty(cmd))
	{
		free_cmd(cmd);
		return (SH_SUCCESS);
	}
	if (pre_exec(cmd) != SH_SUCCESS)
	{
		free_cmd(cmd);
		return (SH_ERR_MALLOC);
	}
	cmd->termios = shell->old_termios;
	ret = exec_pipeline(shell, cmd->pipeline);
	post_exec(shell, cmd, ret);
	return (ret);
}
