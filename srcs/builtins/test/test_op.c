/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:36:33 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/12/10 16:38:19 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int				test_op_type(char op, struct stat buf)
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

static int				resolve_test_op(char op, char *operand)
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

int						test_op(char op, char **av, int ac, int not_op)
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
