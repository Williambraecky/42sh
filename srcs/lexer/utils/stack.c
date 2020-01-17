/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:27:33 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/17 16:17:51 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** NOTE: Only stack push can fail here but it really shouldn't
*/

int		stack_push(t_vec *stack, t_type type)
{
	if (ft_veccpush(stack, &type, sizeof(type)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

t_type	stack_pop(t_vec *stack)
{
	t_type	*type_2;
	t_type	type;

	type_2 = (t_type*)ft_vecpop(stack);
	type = *type_2;
	free(type_2);
	return (type);
}

t_type	stack_top(t_vec *stack)
{
	t_type *type;

	type = (t_type*)ft_vecgettop(stack);
	if (type == NULL)
		return (T_NULL);
	return (*type);
}
