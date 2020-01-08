/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:41:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/08 14:26:42 by ntom             ###   ########.fr       */
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

// clean that if

static int	check_dless_exist(t_lexer *lex, t_type type)
{
	size_t	i;
	t_token	*tok;

	i = 0;
	if (type != T_NEWLINE)
		return (-1);
	while (i < lex->tokens.size)
	{
		tok = (t_token*)ft_vecget(&lex->tokens, i);
		if (!(tok->type == T_DOUBLE_LESSER) || ((t_hdoc*)tok)->completed == 1)
			;
		else if ((i + 1) <= lex->tokens.size
			&& ((t_token*)ft_vecget(&lex->tokens, i + 1))->type == T_WORD)
		{
			if (pipe(((t_hdoc*)tok)->pipe) != 0)
				return (SH_ERR_PIPE);
			if (!(((t_hdoc*)tok)->name =
			ft_strdup(((t_token*)ft_vecget(&lex->tokens, i + 1))->str)))
				return (SH_ERR_MALLOC);
			return (SH_SUCCESS);
		}
		i++;
	}
	return (-1);
}

// pipe(hdoc->pipe)

static int	stack(t_type type, t_lexer *lex)
{
	int		ret;

	ret = SH_SUCCESS;
	if (lex->tokens.size == 1 && g_stackable[type])
		return (ret);
	if (lex->stack.size != 0 &&
		(type != T_SEMICOLON && type != T_AMPERSAND && type != T_NEWLINE))
		stack_pop(lex);
	else if (g_stackable[type])
		ret = stack_push(lex, type);
	else if ((ret = check_dless_exist(lex, type)) == SH_SUCCESS)
		ret = stack_push(lex, T_DOUBLE_LESSER);
	//ft_printf("---> type in stack %s\n", last_stack_type(&lex->stack));
	return (ret);
}

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
