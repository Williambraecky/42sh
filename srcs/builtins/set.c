/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:15:22 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/20 11:52:12 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: defines internal variable + other
*/

static int valid_arg(char *string)
{
		if (ft_strchr(string, '='))
			return (1);
		else
			return (0);
}

int				set_builtin(int argc, char **argv, t_sh *shell)
{
	char **av;

	if (argc == 1)
		ft_mapprint(shell->internals);
	if (argc == 2 && valid_arg(argv[1]))
	{
		av = ft_strsplit(argv[1], '=');
		if (argc == 2 && has_internal(shell, av[0]))
			return (repl_internal(shell, av[0], av[1]));
		else if (argc == 2 && !has_internal(shell, av[0]))
			return (add_internal(shell, av[0], av[1]));
		ft_freesplit(av);
	}
	return (0);
}
