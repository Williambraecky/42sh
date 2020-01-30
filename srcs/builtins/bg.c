/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:26:13 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/30 22:59:30 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"

/*
** NOTE: puts current top job to background (no waiting)
*/

static int	goto_bg(t_sh *shell, t_cmd *cmd)
{
	if (cmd->background)
	{
		ft_dprintf(2, "bg: job already in background\n");
		return (1);
	}
	job_continue(shell, cmd, 0);
	return (0);
}

static int	handle_args(int argc, char **argv, t_sh *shell)
{
	t_cmd	*cmd;
	int		i;

	i = 1;
	while (i < argc)
	{
		cmd = job_by_id(shell, argv[i]);
		if (!cmd)
		{
			ft_dprintf(2, "42sh: bg: %s: no such job\n", argv[i]);
			return (1);
		}
		goto_bg(shell, cmd);
		i++;
	}
	return (0);
}

int			bg_builtin(int argc, char **argv, t_sh *shell)
{
	t_cmd	*cmd;

	if (getpid() != shell->pid || !shell->job_control)
	{
		ft_dprintf(2, "bg: job control currently disabled\n");
		return (1);
	}
	if (argc == 1)
	{
		if (shell->jobs.size == 0)
		{
			ft_dprintf(2, "bg: no current job\n");
			return (1);
		}
		cmd = ft_vecget(&shell->jobs, shell->jobs.size - 1);
		if (goto_bg(shell, cmd))
			return (1);
	}
	return (handle_args(argc, argv, shell));
}
