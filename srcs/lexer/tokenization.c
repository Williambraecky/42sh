/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:22:45 by ntom              #+#    #+#             */
/*   Updated: 2020/01/02 18:31:49 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_tdef		g_def_table[] =
{
	{T_NEWLINE, istok_newline, transform_newline},
	{T_DOUBLE_AMPERSAND, istok_double_ampersand, transform_double_ampersand},
	{T_DOUBLE_PIPE, istok_double_pipe, transform_double_pipe},
	{T_DOUBLE_LESSER, istok_double_lesser, transform_double_lesser},
	{T_DOUBLE_GREATER, istok_double_greater, transform_double_greater},
	{T_LESSER_AND, istok_lesserand, transform_lesserand},
	{T_GREATER_AND, istok_greaterand, transform_greaterand},
	{T_LESSER, istok_lesser, transform_lesser},
	{T_GREATER, istok_greater, transform_greater},
	{T_PIPE, istok_pipe, transform_pipe},
	{T_SEMICOLON, istok_semicolon, transform_semicolon},
	{T_AMPERSAND, istok_ampersand, transform_ampersand},
	{T_WORD, istok_word, transform_word},
	{T_NULL, istok_null, transform_null}
};

/*
** extern char		*g_tab_types[];
**
** static char *last_token_type(t_lexer *lexer)
** {
** 	t_token *token;
**
** 	token = ft_vecgettop(&lexer->tokens);
** 	return (g_tab_types[token->type]);
** }
*/

size_t		g_size = sizeof(g_def_table) / sizeof(*g_def_table);

t_tdef		*determine_type(t_lexer *lexer, t_token *token)
{
	size_t	i;

	i = 0;
	while (i < g_size)
	{
		if (g_def_table[i].is_tok(lexer, token))
			return (&g_def_table[i]);
		i++;
	}
	return (NULL);
}

extern char		*g_tab_types[]; //to remove

int			tokenization(t_lexer *lexer)
{
	t_tdef	*new_tok_def;
	t_token	tok;
	int		res;

	while (lexer->line[lexer->i])
	{
		if ((res = delimit_token(lexer, &tok.str)) != SH_SUCCESS)
			return (res);
		//TODO: check stack if we need to complete input or not (through quotes and dquotes)
		if ((tok.len = ft_strlen(tok.str)) == 0)
		{
			free(tok.str);
			break ;
		}
		if (!(new_tok_def = determine_type(lexer, &tok))
			|| new_tok_def->transform(lexer, &tok))
			return (SH_ERR);
		lexer->i += tok.len;
	}
	//TODO: input is not finished if it doesn't end with a \n
	return (SH_SUCCESS);
}
