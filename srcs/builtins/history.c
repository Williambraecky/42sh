/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:30:04 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/19 14:30:08 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: prints current history in '  %n   %s\n' format
*/

static int	print_history(t_sh *shell, int offset)
{
	int		i;

	if (shell == NULL || !shell->history.vec)
		return (1);
	i = 0;
	while (shell->history.vec[i])
	{
		if (i >= offset)
			ft_printf("%n  %s\n", i, shell->history.vec[i]);
		++i;
	}
	return (0);
}

int			history_builtin(int argc, char **argv, t_sh *shell)
{
	if (argc <= 1)
		print_history(shell, 0);
	else if (argc == 2 && ft_strisnumber(argv[1]))
		print_history(shell, ft_atoi(argv[1]));
	return (0);
}
