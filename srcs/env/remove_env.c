/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:33:46 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/19 15:35:20 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	remove_env(t_sh *shell, char *key)
{
	t_node		*node;
	t_s64		hash;

	if (!has_env(shell, key))
		return ;
	hash = ft_maphash(shell->env, key);
	node = &shell->env->nodes[hash];
	ft_memdel(&node->value);
	ft_strdel(&node->key);
	node->is_used = 0;
}
