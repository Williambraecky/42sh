/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:10:18 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/12/10 16:42:35 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void		parse_cmp_op(char *cmp_op, char *s1, char *s2, int *ret)
{
	if (ft_strequ(cmp_op, "=") && !ft_strequ(s1, s2))
		*ret = 1;
	else if (ft_strequ(cmp_op, "!=") && ft_strequ(s1, s2))
		*ret = 1;
	else if ((!ft_strequ(cmp_op, "!=") && !ft_strequ(cmp_op, "=")))
		*ret = int_cmp(s1, s2, cmp_op);
}

int				cmp_op(char **av, int ac, int not_op)
{
	char	*s1;
	char	*s2;
	char	*cmp_op;
	int		ret;

	if ((not_op && ac > 5) || (!not_op && ac > 4))
	{
		ft_putstr("test: too many arguments\n");
		return (2);
	}
	s1 = not_op ? av[2] : av[1];
	s2 = not_op && ac > 3 ? av[4] : av[3];
	cmp_op = not_op ? av[3] : av[2];
	ret = 0;
	parse_cmp_op(cmp_op, s1, s2, &ret);
	if (ret == 2)
		return (2);
	if (!s2)
	{
		ft_putstr("test: condition expected\n");
		return (2);
	}
	ret = not_op_reverse(ret, not_op);
	return (ret);
}

static int		num_cmp(char *cmp_op, char *s1, char *s2)
{
	if (ft_strequ(cmp_op, "-eq") && (ft_atoi(s1) == ft_atoi(s2)))
		return (0);
	if (ft_strequ(cmp_op, "-ne") && (ft_atoi(s1) != ft_atoi(s2)))
		return (0);
	if (ft_strequ(cmp_op, "-gt") && (ft_atoi(s1) > ft_atoi(s2)))
		return (0);
	if (ft_strequ(cmp_op, "-ge") && (ft_atoi(s1) >= ft_atoi(s2)))
		return (0);
	if (ft_strequ(cmp_op, "-lt") && (ft_atoi(s1) < ft_atoi(s2)))
		return (0);
	if (ft_strequ(cmp_op, "-le") && (ft_atoi(s1) <= ft_atoi(s2)))
		return (0);
	return (1);
}

int				int_cmp(char *s1, char *s2, char *cmp_op)
{
	int i;

	i = -1;
	while (s1[++i])
	{
		if (!ft_isdigit(s1[i]))
		{
			ft_printf("test: integer expression expected: %s\n", s1);
			return (2);
		}
	}
	i = -1;
	while (s2[++i])
	{
		if (!ft_isdigit(s2[i]))
		{
			ft_printf("test: integer expression expected: %s\n", s2);
			return (2);
		}
	}
	return (num_cmp(cmp_op, s1, s2));
}
