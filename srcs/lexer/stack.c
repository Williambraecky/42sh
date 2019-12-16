/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 12:28:46 by ntom              #+#    #+#             */
/*   Updated: 2019/12/16 16:18:26 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			g_compat[] =
{
	[T_DOUBLE_PIPE] = (M_WSPACE | M_NEWLINE),
	[T_DOUBLE_AMPERSAND] = (M_WSPACE | M_NEWLINE),
	[T_QUOTE] = M_QUOTE,
	[T_DOUBLE_QUOTE] = M_DOUBLE_QUOTE,
	[T_PIPE] = (M_WSPACE | M_NEWLINE),
	[T_NULL] = 0
};

char		*g_tab_types[] =
{
	[T_NEWLINE] = "NEWLINE",
	[T_DOUBLE_AMPERSAND] = "DOUBLE_AMPERSAND",
	[T_DOUBLE_PIPE] = "DOUBLE_PIPE",
	[T_DOUBLE_LESSER] = "DOUBLE_LESSER",
	[T_DOUBLE_GREATER] = "DOUBLE_GREATER",
	[T_LESSER_AND] = "LESSER_AND",
	[T_GREATER_AND] = "GREATER_AND",
	[T_LESSER] = "LESSER",
	[T_GREATER] = "GREATER",
	[T_PIPE] = "PIPE",
	[T_QUOTE] = "QUOTE",
	[T_DOUBLE_QUOTE] = "DOUBLE_QUOTE",
	[T_SEMICOLON] = "SEMICOLON",
	[T_AMPERSAND] = "AMPERSAND",
	[T_WSPACE] = "WSPACE",
	[T_WORD] = "WORD",
	[T_NULL] = "NULL"
};

int			g_stackable[] =
{
	[T_DOUBLE_PIPE] = 1,
	[T_DOUBLE_AMPERSAND] = 1,
	[T_QUOTE] = 1,
	[T_DOUBLE_QUOTE] = 1,
	[T_PIPE] = 1,
	[T_NULL] = 0
};

char		*last_stack_type(t_vec *stack)
{
	if (stack->size == 0)
		return ("NULL");
	return (g_tab_types[(*(t_type*)(ft_vecgettop(stack)))]);
}

int			stack(t_type type, t_vec *stack)
{
	if (stack->size == 0 && g_stackable[type])
		return (ft_veccpush(stack, &type, sizeof(type)));
	if ((type == T_QUOTE || type == T_DOUBLE_QUOTE)
		&& type == *((t_type*)ft_vecgettop(stack)))
		free(ft_vecpop(stack));
	else if (g_compat[type] & (1 << type))
		free(ft_vecpop(stack));
	if (g_stackable[type] && (g_compat[type] & (1 << type)))
		return (ft_veccpush(stack, &type, sizeof(type)));
	return (0);
}
