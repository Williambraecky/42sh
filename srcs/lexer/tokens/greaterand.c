/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greaterand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:46:46 by ntom              #+#    #+#             */
/*   Updated: 2019/11/25 15:34:52 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			istok_greaterand(t_lexer *lexer)
{
	if ((lexer->line[lexer->i] == '&' && lexer->line[lexer->i + 1] == '>')
		|| (lexer->line[lexer->i] == '>' && lexer->line[lexer->i + 1] == '&'))
		return (1);
	return (0);
}

int			createtok_greaterand(t_lexer *lexer)
{
	t_token	tok;

	tok.size = sizeof(t_token);
	tok.type = T_GREATER_AND;
	if (!(tok.str = ft_strdup(">&")))
		return (SH_ERR_MALLOC);
	tok.len = 2;
	return (token_process(lexer, &tok));
}
