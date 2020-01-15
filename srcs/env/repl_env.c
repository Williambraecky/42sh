/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:21:58 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 14:25:24 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: replace or add to env
*/

int		repl_env(t_sh *shell, char *key, char *value)
{
	t_s64	hash;
	t_node	*node;

	if (!shell->env)
		return (SH_ERR_NOEXIST);
	if (!(key = ft_strdup(key))
		|| !(value = ft_strdup(value)))
	{
		free(key);
		free(value);
		return (SH_ERR_MALLOC);
	}
	if (ft_strequ(key, "PATH"))
		path_change(shell);
	if (ft_mapcontains(shell->env, key))
	{
		hash = ft_maphash(shell->env, key);
		node = &shell->env->nodes[hash];
		ft_strdel(&node->key);
		ft_strdel((char**)&node->value);
		node->is_used = 0;
	}
	if (ft_mapputnoclone(shell->env, key, value, ft_strlen(value)) != MAP_OK)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
