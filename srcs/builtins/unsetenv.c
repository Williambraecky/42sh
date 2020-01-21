/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:34:54 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 23:50:24 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		unsetenv_builtin(int argc, char **argv, t_sh *shell)
{
	int		i;

	i = 1;
	while (i < argc)
		remove_env(shell, argv[i++]);
	return (0);
}
