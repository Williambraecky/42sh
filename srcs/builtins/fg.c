/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:25:11 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/30 22:59:34 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"

/*
** NOTE: puts current top job to foreground and waits
*/

static size_t	job_index(t_sh *shell, t_cmd *cmd)
{
	size_t	i;

	i = shell->jobs.size;
	while (i--)
		if (ft_vecget(&shell->jobs, i) == cmd)
			return (i);
	return (i);
}

static int		goto_fg(t_sh *shell, t_cmd *cmd)
{
	ft_printf("%s\n", cmd->cmd_str);
	ft_vecdel(&shell->jobs, job_index(shell, cmd));
	job_continue(shell, cmd, 1);
	return (0);
}

static int		handle_args(int argc, char **argv, t_sh *shell)
{
	t_cmd	*cmd;
	int		i;

	i = 1;
	while (i < argc)
	{
		cmd = job_by_id(shell, argv[i]);
		if (!cmd)
		{
			ft_dprintf(2, "42sh: fg: %s: no such job\n", argv[i]);
			return (get_exit_code(shell));
		}
		ft_printf("%s\n", cmd->cmd_str);
		goto_fg(shell, cmd);
		i++;
	}
	return (get_exit_code(shell));
}

int				fg_builtin(int argc, char **argv, t_sh *shell)
{
	t_cmd	*cmd;

	if (getpid() != shell->pid || !shell->job_control)
	{
		ft_dprintf(2, "fg: job control currently disabled\n");
		return (1);
	}
	if (argc == 1)
	{
		if (shell->jobs.size == 0)
		{
			ft_dprintf(2, "fg: no current job\n");
			return (1);
		}
		cmd = ft_vecget(&shell->jobs, shell->jobs.size - 1);
		if (goto_fg(shell, cmd))
			return (1);
	}
	return (handle_args(argc, argv, shell));
}
