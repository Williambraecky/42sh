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

static int print_history(t_sh *shell, int startfrom)
{
	int		i;

	if (shell == NULL || !shell->history.vec)
		return (1);
	i = startfrom;
	while (shell->history.vec[i])
	{
		ft_printf("%n  %s\n", i, shell->history.vec[i]);
		++i;
	}
	return (0);
}

int		history_builtin(int argc, char **argv, t_sh *shell)
{
	(void)argc;
	(void)argv;
	(void)shell;
	if (argc <= 2 && ft_strcmp(argv[1], "-n") != 0)
		print_history(shell, 0);
	return (0);
}
