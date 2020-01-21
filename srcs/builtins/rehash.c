/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rehash.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:23:05 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 23:30:26 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: cleans hash table
*/

int		rehash_builtin(int argc, char **argv, t_sh *shell)
{
	size_t	i;

	(void)argc;
	(void)argv;
	i = 0;
	while (i < shell->use_hash->max_size)
	{
		if (shell->use_hash->nodes[i].is_used)
			remove_hash(shell, shell->use_hash->nodes[i].key);
		i++;
	}
	return (0);
}
