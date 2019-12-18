/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:30:04 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 18:35:38 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: prints current history in '  %n   %s\n' format
*/

static void print_history(t_sh *shell)
{
	int		i;

	if (!shell || !shell->history || !shell->history.vec)
		return (1);
	i = 0
	while (shell->history.vec && shell->history.vec[i])
	{
		ft_printf("%n  %s\n", i, (char *)shell->history.vec[i]);
		++i;
	}
	return (0);
}

int		history_builtin(int argc, char **argv, t_sh *shell)
{
	(void)argc;
	(void)argv;
	(void)shell;
	return (0);
}
