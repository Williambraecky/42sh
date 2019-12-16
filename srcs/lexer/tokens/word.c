/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:15:50 by ntom              #+#    #+#             */
/*   Updated: 2019/12/12 14:58:02 by ntom             ###   ########.fr       */
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
	(void)lexer;
	return (1);
}

int			createtok_word(t_lexer *lexer)
{
	t_word	tok;
	size_t	len;

	len = 0;
	tok.token.size = sizeof(t_word);
	tok.token.type = T_WORD;
	// TODO : add check stack
	while ((lexer->line + lexer->i)[len]
		&& (!(is_word_charset((lexer->line + lexer->i)[len]))
		|| is_char_escaped(lexer->line, lexer->i + len)))
		len++;
	if (!(tok.token.str = ft_strndup(lexer->line + lexer->i, len)))
		return (SH_ERR_MALLOC);
	tok.token.len = len;
	token_process(lexer, (t_token*)&tok);
	return (SH_SUCCESS);
}
