/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_internal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:34:43 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/19 15:35:08 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	remove_internal(t_sh *shell, char *key)
{
	t_node		*node;
	t_s64		hash;

	if (!has_internal(shell, key))
		return ;
	hash = ft_maphash(shell->internals, key);
	node = &shell->internals->nodes[hash];
	ft_memdel(&node->value);
	ft_strdel(&node->key);
	node->is_used = 0;
}
