/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:26:13 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 19:15:02 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"

/*
** NOTE: puts current top job to background (no waiting)
** TODO: job id as argument
*/

int		bg_builtin(int argc, char **argv, t_sh *shell)
{
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	if (shell->jobs.size == 0)
	{
		ft_dprintf(2, "bg: no current job\n");
		return (1);
	}
	cmd = ft_vecget(&shell->jobs, shell->jobs.size - 1);
	if (cmd->background)
	{
		ft_dprintf(2, "bg: job already in background\n");
		return (1);
	}
	job_continue(shell, cmd, 0);
	return (0);
}
