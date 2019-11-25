/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_ampersand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:08:24 by ntom              #+#    #+#             */
/*   Updated: 2019/11/25 15:34:47 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			istok_double_ampersand(t_lexer *lexer)
{
	if (lexer->line[lexer->i] == '&' && lexer->line[lexer->i + 1] == '&')
		return (1);
	return (0);
}

int			createtok_double_ampersand(t_lexer *lexer)
{
	t_token	tok;

	tok.size = sizeof(t_token);
	tok.type = T_DOUBLE_AMPERSAND;
	if (!(tok.str = ft_strdup("&&")))
		return (SH_ERR_MALLOC);
	tok.len = 2;
	return (token_process(lexer, &tok));
}
