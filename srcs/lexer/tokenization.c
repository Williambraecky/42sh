/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:22:45 by ntom              #+#    #+#             */
/*   Updated: 2019/12/16 16:13:51 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_tdef		g_def_table[] =
{
	{T_NEWLINE, istok_newline, createtok_newline},
	{T_DOUBLE_AMPERSAND, istok_double_ampersand, createtok_double_ampersand},
	{T_DOUBLE_PIPE, istok_double_pipe, createtok_double_pipe},
	{T_DOUBLE_LESSER, istok_double_lesser, createtok_double_lesser},
	{T_DOUBLE_GREATER, istok_double_greater, createtok_double_greater},
	{T_LESSER_AND, istok_lesserand, createtok_lesserand},
	{T_GREATER_AND, istok_greaterand, createtok_greaterand},
	{T_LESSER, istok_lesser, createtok_lesser},
	{T_GREATER, istok_greater, createtok_greater},
	{T_PIPE, istok_pipe, createtok_pipe},
	{T_QUOTE, istok_quote, createtok_quote},
	{T_DOUBLE_QUOTE, istok_double_quote, createtok_double_quote},
	{T_SEMICOLON, istok_semicolon, createtok_semicolon},
	{T_AMPERSAND, istok_ampersand, createtok_ampersand},
	{T_WSPACE, istok_whitespace, createtok_whitespace},
	{T_WORD, istok_word, createtok_word},
	{T_NULL, istok_null, createtok_null}
};

extern char		*g_tab_types[];

/*
** static char *last_token_type(t_lexer *lexer)
** {
** 	t_token *token;
**
** 	token = ft_vecgettop(&lexer->tokens);
** 	return (g_tab_types[token->type]);
** }
*/

size_t		g_size = sizeof(g_def_table) / sizeof(*g_def_table);

t_tdef		*get_next_def(t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (i < g_size)
	{
		if (g_def_table[i].is_tok(lexer))
			return (&g_def_table[i]);
		i++;
	}
	return (NULL);
}

int			tokenization(t_lexer *lexer)
{
	t_tdef	*new_tok_def;

	while (lexer->line[lexer->i])
	{
		if (!(new_tok_def = get_next_def(lexer))
			|| new_tok_def->create_tok(lexer))
			return (SH_ERR);
	}
	//TODO: is stack is not empty get rest of line
	return (SH_SUCCESS);
}
