/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:13:01 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/11/26 13:10:00 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_wspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\f' || c == '\r' || c == '\v');
}

int			istok_whitespace(t_lexer *lexer)
{
	return (is_wspace(lexer->line[lexer->i]));
}

int			createtok_whitespace(t_lexer *lexer)
{
	t_token	tok;
	size_t	len;

	len = 0;
	while (is_wspace(lexer->line[lexer->i + len]))
		len++;
	tok.size = sizeof(t_token);
	tok.type = T_WSPACE;
	if (!(tok.str = ft_strndup(lexer->line, len)))
		return (SH_ERR_MALLOC);
	tok.len = len;
	return (token_process(lexer, &tok));
}
