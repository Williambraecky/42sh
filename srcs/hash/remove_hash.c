/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:30:45 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 22:52:15 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	remove_hash(t_sh *shell, char *bin)
{
	t_node		*node;
	t_s64		hash;
	t_hashed	*hashed;

	if (!has_hash(shell, bin))
		return ;
	hash = ft_maphash(shell->use_hash, bin);
	node = &shell->use_hash->nodes[hash];
	hashed = node->value;
	free(hashed->path);
	ft_memdel(&node->value);
	ft_strdel(&node->key);
	node->is_used = 0;
	shell->use_hash->size--;
}
