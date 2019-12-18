/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:19:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/18 16:13:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: should only handle -n as option
*/

int		echo_builtin(int argc, char **argv, t_sh *shell)
{
	size_t	i;

	(void)shell;
	i = 1;
	if (argc >= 2 && ft_strequ(argv[1], "-n"))
		i = 2;
	while (i < (size_t)argc)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		i++;
		if (i != (size_t)argc)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
	return (0);
}
