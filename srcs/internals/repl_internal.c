/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:21:58 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/19 15:25:29 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: replace or add to env
*/

int		repl_internal(t_sh *shell, char *key, char *value)
{
	t_s64	hash;
	t_node	*node;

	if (!shell->internals)
		return (SH_ERR_NOEXIST);
	if (!(key = ft_strdup(key))
		|| !(value = ft_strdup(value)))
		return (SH_ERR_MALLOC);
	if (ft_mapcontains(shell->internals, key))
	{
		hash = ft_maphash(shell->internals, key);
		node = &shell->internals->nodes[hash];
		ft_strdel(&node->key);
		ft_strdel((char**)&node->value);
		node->is_used = 0;
	}
	if (ft_mapputnoclone(shell->internals, key,
		value, ft_strlen(value)) != MAP_OK)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
