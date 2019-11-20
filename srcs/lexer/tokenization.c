/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:22:45 by ntom              #+#    #+#             */
/*   Updated: 2019/11/20 22:50:43 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_tdef		g_def_table[] =
{
	{T_NEWLINE, istok_newline, createtok_newline},
	{T_AMPERSAND, istok_ampersand, createtok_ampersand},
	{T_DOUBLE_AMPERSAND, istok_double_ampersand, createtok_double_ampersand},
	{T_DOUBLE_PIPE, istok_double_pipe, createtok_double_pipe},
	{T_DOUBLE_QUOTE, istok_double_quote, createtok_double_quote},
	{T_GREATER, istok_greater, createtok_greater},
	{T_GREATER_AND, istok_greaterand, createtok_greaterand},
	{T_LESSER, istok_lesser, createtok_lesser},
	{T_LESSER_AND, istok_lesserand, createtok_lesserand},
	{T_PIPE, istok_pipe, createtok_pipe},
	{T_QUOTE, istok_quote, createtok_quote},
	{T_SEMICOLON, istok_semicolon, createtok_semicolon},
};

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
		if (!(new_tok_def = get_next_def(lexer)))
			return (SH_ERR);
	}
	//TODO: is stack is not empty get rest of line
	return (SH_SUCCESS);
}
