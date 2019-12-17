/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 19:24:03 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/12/16 22:04:58 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int		is_cmp_op(char *str)
{
	if (ft_strequ("=", str) || ft_strequ("!=", str) || ft_strequ("-eq", str) ||
	ft_strequ("-ne", str) || ft_strequ("-gt", str) || ft_strequ("-ge", str) ||
	ft_strequ("-lt", str) || ft_strequ("-le", str))
		return (1);
	return (0);
}

static int		is_test_op(char *str)
{
	if (ft_strequ("-b", str) || ft_strequ("-c", str) || ft_strequ("-d", str) ||
	ft_strequ("-e", str) || ft_strequ("-f", str) || ft_strequ("-g", str) ||
	ft_strequ("-r", str) || ft_strequ("-p", str) || ft_strequ("-L", str) ||
	ft_strequ("-S", str) || ft_strequ("-s", str) || ft_strequ("-u", str) ||
	ft_strequ("-b", str) || ft_strequ("-b", str) || ft_strequ("-w", str) ||
	ft_strequ("-b", str) || ft_strequ("-x", str) || ft_strequ("-z", str))
		return (1);
	return (0);
}

int				not_op_reverse(int ret, int not_op)
{
	if (not_op)
	{
		if (ret)
			ret = 0;
		else
			ret = 1;
	}
	return (ret);
}

int				test_builtin(int ac, char **av, t_sh *shell)
{
	int not_op;
	int ret;

	(void)shell;
	if (ac == 1)
		return (1);
	not_op = ft_strequ(av[1], "!") ? 1 : 0;
	if ((is_test_op(av[1]) && !is_cmp_op(av[2])) ||
	(not_op && is_test_op(av[2]) && !is_cmp_op(av[3])))
		return (test_op(av[1][1], av, ac, not_op));
	if ((is_cmp_op(av[2]) && !not_op) || (not_op && is_cmp_op(av[3])))
		return (cmp_op(av, ac, not_op));
	if ((not_op && ac > 3) || (!not_op && ac > 2))
	{
		ft_printf("ici\n");
		ft_putstr("test: too many arguments\n");
		return (2);
	}
	ret = 0;
	if ((not_op && !av[2]) || (!not_op && !av[1]))
		ret = 1;
	return (not_op_reverse(ret, not_op));
}
