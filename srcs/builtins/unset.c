/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:18:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 23:50:07 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: unsets internal variable from internals table
*/

int		unset_builtin(int argc, char **argv, t_sh *shell)
{
	int		i;

	i = 1;
	while (i < argc)
		remove_internal(shell, argv[i++]);
	return (0);
}
