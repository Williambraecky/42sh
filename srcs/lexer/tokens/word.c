/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:15:50 by ntom              #+#    #+#             */
/*   Updated: 2019/11/26 13:56:39 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_word_charset(char c)
{
	return (c == ' ' || c == '\t' || c == '\f' || c == '\r' || c == '\v'
		|| c == '&' || c == '>' || c == '<' || c == '|' || c == '"'
		|| c == '\n' || c == '\'' || c == ';');
}

// Add macro with charset to not forget to add tokens in the future?

int			istok_word(t_lexer *lexer)
{
	return (is_word_charset(lexer->line[lexer->i]));
}

int			createtok_word(t_lexer *lexer)
{
	t_token	tok;
	size_t	len;

	len = 0;
	tok.size = sizeof(t_token);
	tok.type = T_WORD;
	while (is_word_charset((lexer->line + lexer->i)[len]))
		len++;
	if (!(tok.str = ft_strndup(lexer->line + lexer->i, len)))
		return (SH_ERR_MALLOC);
	tok.len = len;
	token_process(lexer, &tok);
	return (SH_SUCCESS);
}
