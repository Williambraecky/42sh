/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:27:33 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/17 19:46:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** NOTE: Only stack push can fail here but it really shouldn't
*/

int		stack_push(t_vec *stack, t_type type)
{
	if (ft_vecpush(stack, (void*)type))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

int		stack_push_or_pop(t_vec *stack, t_type type)
{
	t_type	type_2;

	type_2 = stack_top(stack);
	if (type != type_2)
		return (stack_push(stack, type));
	stack_pop(stack);
	return (SH_SUCCESS);
}

t_type	stack_pop(t_vec *stack)
{
	return ((t_type)ft_vecpop(stack));
}

t_type	stack_top(t_vec *stack)
{
	if (stack->size == 0)
		return (T_NULL);
	return ((t_type)ft_vecgettop(stack));
}
