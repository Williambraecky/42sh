/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:25:11 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 19:14:35 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"

/*
** NOTE: puts current top job to foreground and waits
** TODO: job id as argument
*/

int		fg_builtin(int argc, char **argv, t_sh *shell)
{
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	if (shell->jobs.size == 0)
	{
		ft_dprintf(2, "fg: no current job\n");
		return (1);
	}
	cmd = ft_vecget(&shell->jobs, shell->jobs.size - 1);
	ft_vecdel(&shell->jobs, shell->jobs.size - 1);
	job_continue(shell, cmd, 1);
	return (get_last_return_code(shell));
}
