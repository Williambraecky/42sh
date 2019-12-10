/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 19:24:03 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/12/10 15:50:06 by wbraeckm         ###   ########.fr       */
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

int				test_op_type(char op, struct stat buf)
{
	if (op == 'b' && !S_ISBLK(buf.st_mode))
		return (1);
	if (op == 'c' && !S_ISCHR(buf.st_mode))
		return (1);
	if (op == 'd' && !S_ISDIR(buf.st_mode))
		return (1);
	if (op == 'f' && !S_ISREG(buf.st_mode))
		return (1);
	if (op == 'g' && !(buf.st_mode & S_ISGID))
		return (1);
	if (op == 'L' && !S_ISLNK(buf.st_mode))
		return (1);
	if (op == 'S' && !S_ISSOCK(buf.st_mode))
		return (1);
	if (op == 's' && buf.st_size <= 0)
		return (1);
	if (op == 'u' && !(buf.st_mode & S_ISUID))
		return (1);
	if (op == 'p' && !S_ISFIFO(buf.st_mode))
		return (1);
	return (0);
}

int				resolve_test_op(char op, char *operand)
{
	struct stat buf;

	if (!operand)
		return (0);
	if (op == 'z')
		return (1);
	if (op == 'e' && access(operand, F_OK) == -1)
		return (1);
	if (op == 'r' && access(operand, R_OK) == -1)
		return (1);
	if (op == 'w' && access(operand, W_OK) == -1)
		return (1);
	if (op == 'x' && access(operand, X_OK) == -1)
		return (1);
	if (lstat(operand, &buf) == -1)
		return (1);
	return (test_op_type(op, buf));
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
	if (ft_strequ(cmp_op, "=") && !ft_strequ(s1, s2))
		ret = 1;
	else if (ft_strequ(cmp_op, "!=") && ft_strequ(s1, s2))
		ret = 1;
	else if ((!ft_strequ(cmp_op, "!=") && !ft_strequ(cmp_op, "=")))
	{
		ret = int_cmp(s1, s2, cmp_op);
		if (ret == 2)
			return (2);
	}
	if (!s2)
	{
		ft_putstr("test: condition expected\n");
		return (2);
	}
	ret = not_op_reverse(ret, not_op);
	return (ret);
}

int				test_op(char op, char **av, int ac, int not_op)
{
	char	*operand;
	int		ret;

	op = not_op == 1 ? av[2][1] : op;
	if ((not_op && ac > 4) || (!not_op && ac > 3))
	{
		ft_putstr("test: too many arguments\n");
		return (2);
	}
	operand = not_op == 1 ? av[3] : av[2];
	ret = resolve_test_op(op, operand);
	ret = not_op_reverse(ret, not_op);
	return (ret);
}

int				test_main(int ac, char **av, t_sh *shell)
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
