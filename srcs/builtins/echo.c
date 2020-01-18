/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:19:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/18 01:08:50 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: should only handle -n as option
*/

int		echo_builtin(int argc, char **argv, t_sh *shell)
{
	size_t	i;
	int		n_flag;

	(void)shell;
	n_flag = 0;
	if (argc >= 2 && ft_strequ(argv[1], "-n"))
		n_flag = 1;
	i = 1 + n_flag;
	while (i < (size_t)argc)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		i++;
		if (i != (size_t)argc)
			write(1, " ", 1);
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}
