/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 12:28:46 by ntom              #+#    #+#             */
/*   Updated: 2019/12/10 16:46:30 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int 	g_compat[] =
{
	[T_DOUBLE_PIPE] = ~M_WSPACE,
	[T_DOUBLE_AMPERSAND] = ~M_WSPACE,
	[T_QUOTE] = M_DOUBLE_QUOTE,
	[T_DOUBLE_QUOTE] = M_QUOTE,
	[T_PIPE] = ~M_WSPACE
};

int			stack(t_type type, t_vec *stack)
{
	if (stack->size == 0)
		return (ft_veccpush(stack, &type, sizeof(type)));
	if (type == (unsigned int)stack->vec)
		free(ft_vecpop(stack));
	else if (g_compat[type] & (1 << type))
	{
		return (0);
	}
	return (0);
}
