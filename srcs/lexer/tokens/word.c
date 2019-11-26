/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:15:50 by ntom              #+#    #+#             */
/*   Updated: 2019/11/26 16:15:30 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_word_charset(char c)
{
	const char	*charset = " \t\f\r&><|\"\n';";
	int			i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int			istok_word(t_lexer *lexer)
{
	if (lexer)
		;
	return (1);
}

int			createtok_word(t_lexer *lexer)
{
	t_token	tok;
	size_t	len;

	len = 0;
	tok.size = sizeof(t_token);
	tok.type = T_WORD;
	// TODO : add check stack
	while (!(is_word_charset((lexer->line + lexer->i)[len]))
		|| is_char_escaped(lexer->line, lexer->i + len))
		len++;
	if (!(tok.str = ft_strndup(lexer->line + lexer->i, len)))
		return (SH_ERR_MALLOC);
	tok.len = len;
	token_process(lexer, &tok);
	return (SH_SUCCESS);
}
