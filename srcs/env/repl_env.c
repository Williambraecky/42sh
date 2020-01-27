/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:21:58 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 17:00:12 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: replace or add to env
*/

int		repl_env(t_sh *shell, char *k, char *v)
{
	t_s64	hash;
	t_node	*node;

	if (!shell->env)
		return (SH_ERR_NOEXIST);
	if (!(k = ft_strdup(k))
		|| !(v = ft_strdup(v)))
	{
		free(k);
		free(v);
		return (SH_ERR_MALLOC);
	}
	if (ft_strequ(k, "PATH"))
		path_change(shell);
	if (ft_mapcontains(shell->env, k))
	{
		hash = ft_maphash(shell->env, k);
		node = &shell->env->nodes[hash];
		ft_strdel(&node->key);
		ft_strdel((char**)&node->value);
		node->is_used = 0;
	}
	if (ft_mapputnoclone(shell->env, k, v, ft_strlen(v) + 1) != MAP_OK)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
