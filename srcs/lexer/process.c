/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:41:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/07 14:32:29 by ntom             ###   ########.fr       */
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

static int	check_t_word_exist(t_lexer *lex)
{
	size_t	i;

	i = 0;
	while (i < lex->tokens.size)
	{
		if (((t_token*)ft_vecget(&lex->tokens, i))->type == T_WORD)
			return (1);
		i++;
	}
	return (0);
}

static int	stack(t_type type, t_lexer *lex)
{
	if (!(check_t_word_exist(lex)) &&
		(type == T_PIPE || type == T_DOUBLE_PIPE || type == T_DOUBLE_AMPERSAND))
		return (SH_ERR_SYNTAX);
	if (lex->stack.size != 0 &&
		(type != T_SEMICOLON && type != T_AMPERSAND
		&& type != T_NEWLINE && type != T_WSPACE))
		stack_pop(lex);
	else if (g_stackable[type])
		ft_veccpush(&lex->stack, &type, sizeof(type));
	//ft_printf("---> type in stack %s\n", last_stack_type(&lex->stack));
	return (0);
}

/*
** add only if word exists before
** and wait for a delimiter ; \n &
** | || &&
*/

int			token_process(t_lexer *lexer, t_token *token)
{
	if (ft_veccpush(&lexer->tokens, token, token->size))
		return (SH_ERR_MALLOC);
	//ft_printf("Last token type %s, str %s\n", last_token_type(lexer), token->str); // to remove
	stack(token->type, lexer);
	return (SH_SUCCESS);
}
