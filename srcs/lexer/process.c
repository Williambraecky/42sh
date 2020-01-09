/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:41:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/09 12:06:18 by ntom             ###   ########.fr       */
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

/*
** static char *last_token_type(t_lexer *lexer)
** {
** 	t_token *token;
**
** 	token = ft_vecgettop(&lexer->tokens);
** 	return (g_tab_types[token->type]);
** }
*/

/*
** char		*last_stack_type(t_vec *stack)
** {
** 	if (stack->size == 0)
** 		return ("NULL");
** 	return (g_tab_types[(*(t_type*)(ft_vecgettop(stack)))]);
** }
*/

static int	find_parse_error(t_type type, t_lexer *lex)
{
	if ((lex->tokens.size == 1 && g_stackable[type])
		|| (g_stackable[type] &&
			((t_token*)ft_vecget(&lex->tokens, lex->tokens.size - 2))->type
			!= T_WORD))
		return (SH_ERR_SYNTAX);
	return (SH_SUCCESS);
}

static int	check_dless_exist(t_lexer *lex, t_type type)
{
	size_t	i;
	t_token	*tok;

	i = 0;
	if (type != T_NEWLINE)
		return (SH_SUCCESS);
	while (i < lex->tokens.size)
	{
		tok = (t_token*)ft_vecget(&lex->tokens, i);
		if ((tok->type == T_DOUBLE_LESSER) && ((t_hdoc*)tok)->completed == 0)
		{
			if ((i + 1) < lex->tokens.size
				&& ((t_token*)ft_vecget(&lex->tokens, i + 1))->type != T_WORD
				&& (lex->stack_completed = 1) == 1)
				return (SH_ERR_SYNTAX);
			if (remove_quotes(((t_token*)ft_vecget(&lex->tokens, i + 1))->str,
				&((t_hdoc*)tok)->name) != SH_SUCCESS)
				return (SH_ERR_MALLOC);
			if (pipe(((t_hdoc*)tok)->pipe) != 0)
				return (SH_ERR_PIPE);
			return (stack_push(lex, T_DOUBLE_LESSER));
		}
		i++;
	}
	return (SH_SUCCESS);
}

static int	stack(t_type type, t_lexer *lex)
{
	int		ret;

	ret = SH_SUCCESS;
	if ((ret = find_parse_error(type, lex)) != SH_SUCCESS)
		lex->stack_completed = 1;
	else if (lex->stack.size != 0 &&
		(type != T_SEMICOLON && type != T_AMPERSAND && type != T_NEWLINE))
		stack_pop(lex);
	else if (g_stackable[type])
		ret = stack_push(lex, type);
	else
		ret = check_dless_exist(lex, type);
	//ft_printf("---> type in stack %s int %d\n", last_stack_type(&lex->stack), lex->stack_completed);
	return (ret);
}

// TO DO
// if heredoc active in stack do a while read not = the name
// write dans pipe[1]
// handle stack not empty in new handle prompt

int			token_process(t_lexer *lexer, t_token *token)
{
	int		ret;

	ret = SH_SUCCESS;
	if (ft_veccpush(&lexer->tokens, token, token->size))
		return (SH_ERR_MALLOC);
	//ft_printf("Last token type %s, str %s\n", last_token_type(lexer), token->str); // to remove
	ret = stack(token->type, lexer);
	return (ret);
}
