/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:25:11 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 21:52:26 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"

/*
** NOTE: puts current top job to foreground and waits
** TODO: job id as argument
*/

static int	goto_fg(t_sh *shell, t_cmd *cmd)
{
	ft_printf("%s\n", cmd->cmd_str);
	job_continue(shell, cmd, 1);
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
			return (get_last_return_code(shell));
		}
		ft_printf("%s\n", cmd->cmd_str);
		goto_fg(shell, cmd);
		i++;
	}
	return (get_last_return_code(shell));
}

int		fg_builtin(int argc, char **argv, t_sh *shell)
{
	t_cmd	*cmd;

	if (argc == 1)
	{
		if (shell->jobs.size == 0)
		{
			ft_dprintf(2, "bg: no current job\n");
			return (1);
		}
		cmd = ft_vecget(&shell->jobs, shell->jobs.size - 1);
		if (goto_fg(shell, cmd))
			return (1);
	}
	return (handle_args(argc, argv, shell));
}
