/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:55:44 by ntom              #+#    #+#             */
/*   Updated: 2019/11/25 15:34:56 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			istok_quote(t_lexer *lexer)
{
	if (lexer->line[lexer->i] == '\'')
		return (1);
	return (0);
}

int			createtok_quote(t_lexer *lexer)
{
	t_token	tok;

	tok.size = sizeof(t_token);
	tok.type = T_QUOTE;
	if (!(tok.str = ft_strdup("'")))
		return (SH_ERR_MALLOC);
	tok.len = 1;
	return (token_process(lexer, &tok));
}
