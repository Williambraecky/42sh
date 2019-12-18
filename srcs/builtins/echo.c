/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:19:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 18:33:06 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: should only handle -n as option
*/

int		echo_builtin(int argc, char **argv, t_sh *shell)
{
	int		i;
	int		no_nl;

	if (ac <= 1)
		ft_putchar_fd('\n', STDOUT);
	else
	{
		no_nl = 0;
		if (av[1] && ft_strlen(av[1]) <= 2 && av[1][0] == '-' && av[1][1] == 'n')
		{
			no_nl = 1;
			i = 2;
		}
		else
			i = 1;
		while (i < ac)
		{
			ft_putstr_fd(s, STDOUT);
			if (i < ac - 1)
				ft_putchar_fd(' ', STDOUT);
			++i;
		}
		if (!no_nl)
			ft_putchar_fd('\n', STDOUT);
	}
	return (0);
}
