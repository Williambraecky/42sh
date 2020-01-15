/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:22:33 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 14:24:12 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	map_hash_filter(t_node *node)
{
	t_hashed	*hashed;

	hashed = node->value;
	free(hashed->path);
	free(node->value);
	free(node->key);
	return (0);
}

/*
** NOTE: function to be called whenever PATH changes
** NOTE: this should reset the hash table
*/

void		path_change(t_sh *shell)
{
	ft_mapfilter(shell->use_hash, map_hash_filter);
}
