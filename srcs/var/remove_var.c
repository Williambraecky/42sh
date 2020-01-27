/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 21:40:04 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 22:08:10 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		remove_var(t_sh *shell, char *key)
{
	t_node	*node;
	t_var	*var;
	t_s64	hash;

	if (!has_var(shell, key))
		return ;
	if (ft_strequ(key, "PATH"))
		path_change(shell);
	hash = ft_maphash(shell->vars, key);
	node = &shell->vars->nodes[hash];
	var = node->value;
	ft_strdel(&var->var);
	ft_memdel(&node->value);
	ft_strdel(&node->key);
	node->is_used = 0;
	shell->vars->size--;
}
