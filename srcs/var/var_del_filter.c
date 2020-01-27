/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_del_filter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 22:45:51 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 22:46:05 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			var_del_filter(t_node *node)
{
	t_var	*var;

	var = (t_var*)node->value;
	ft_strdel(&var->var);
	ft_memdel(&node->value);
	ft_strdel(&node->key);
	return (0);
}
