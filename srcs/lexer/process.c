/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:41:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/06 15:05:21 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
	[T_IO_NUMBER] = "IO_NUMBER",
	[T_WORD] = "WORD",
	[T_NULL] = "NULL"
};

int			g_stackable[] =
{
	[T_DOUBLE_PIPE] = 1,
	[T_DOUBLE_AMPERSAND] = 1,
	[T_PIPE] = 1,
	[T_DOUBLE_LESSER] = 1,
	[T_NULL] = 0
};


// static char *last_token_type(t_lexer *lexer)
// {
// 	t_token *token;
//
// 	token = ft_vecgettop(&lexer->tokens);
// 	return (g_tab_types[token->type]);
// }

// char		*last_stack_type(t_vec *stack)
// {
// 	if (stack->size == 0)
// 		return ("NULL");
// 	return (g_tab_types[(*(t_type*)(ft_vecgettop(stack)))]);
// }

int			stack(t_type type, t_vec *stack)
{
	if (g_stackable[type])
	{
		ft_veccpush(stack, &type, sizeof(type));
		//ft_printf("---> type in stack %s\n", last_stack_type(stack));
		return (1);
	}
	return (0);
}

int		token_process(t_lexer *lexer, t_token *token)
{
	if (ft_veccpush(&lexer->tokens, token, token->size))
		return (SH_ERR_MALLOC);
	//ft_printf("Last token type %s, str %s\n", last_token_type(lexer), token->str); // to remove
	stack(token->type, &lexer->stack);
	return (SH_SUCCESS);
}
