/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:15:22 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 18:38:21 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: defines internal variable + other
*/

static int valid_arg(char *string)
{
		if (ft_strchr(string, '='))
			return (0);
		else
			return (1);
}

int				set_builtin(int argc, char **argv, t_sh *shell)
{
	if (argc == 1)
		ft_mapprint(shell->internals);
	else if (argc == 2 && valid_arg(argv[1]) && has_internal(shell, argv[1]))
		return (repl_internal(shell, argv[1], argv[2]));
	else if (argc == 2 && valid_arg(argv[1]) && !has_internal(shell, argv[1]))
		return (add_internal(shell, argv[1], argv[2]));
	return (0);
}
