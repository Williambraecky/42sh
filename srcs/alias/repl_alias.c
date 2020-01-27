/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <wdaher-a@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:04:37 by wdaher-a          #+#    #+#             */
/*   Updated: 2020/01/27 17:34:37 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: replace or add alias
*/

int		repl_alias(t_sh *shell, char *key, char *value)
{
	t_s64	hash;
	t_node	*node;

	if (!shell->aliases)
		return (SH_ERR_NOEXIST);
	if (!(key = ft_strdup(key))
		|| !(value = ft_strdup(value)))
	{
		free(key);
		free(value);
		return (SH_ERR_MALLOC);
	}
	if (ft_mapcontains(shell->aliases, key))
	{
		hash = ft_maphash(shell->aliases, key);
		node = &shell->aliases->nodes[hash];
		ft_strdel(&node->key);
		ft_strdel((char**)&node->value);
		node->is_used = 0;
	}
	if (ft_mapputnoclone(shell->aliases, key,
		value, ft_strlen(value) + 1) != MAP_OK)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
