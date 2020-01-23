/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:34:52 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/23 16:52:30 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern int	g_optind;
extern int	g_optopt;

static int	remove_all_aliases(t_sh *shell, int argc)
{
	if (argc)
	{
		ft_dprintf(2, "42sh: unalias: -a: too many arguments\n");
		return (1);
	}
	ft_mapfilter(shell->aliases, map_del_filter);
	return (0);
}

static int	remove_args(t_sh *shell, int argc, char **argv)
{
	int		i;
	int		err;

	i = 0;
	err = 0;
	while (i < argc)
	{
		if (!has_alias(shell, argv[i]))
		{
			ft_dprintf(2, "42sh: unalias: no such hash table element: b\n");
			err++;
		}
		else
			remove_alias(shell, argv[i]);
		i++;
	}
	return (err > 0);
}

int			unalias_builtin(int argc, char **argv, t_sh *shell)
{
	int		a_flag;
	int		ret;

	a_flag = 0;
	while ((ret = ft_getopt(argc, argv, "a")) != -1)
	{
		if (ret == 'r')
			a_flag = 1;
		else
		{
			ft_dprintf(2, "42sh: unalias: -%c: invalid option\n", g_optopt);
			return (1);
		}
	}
	argc -= g_optind;
	argv += g_optind;
	if (argc == 0 && !a_flag)
		ft_dprintf(2, "42sh: unalias: not enough arguments\n");
	if (a_flag)
		return (remove_all_aliases(shell, argc));
	else
		return (remove_args(shell, argc, argv));
	return (1);
}
