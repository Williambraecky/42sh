/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ampersand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:06:46 by ntom              #+#    #+#             */
/*   Updated: 2019/12/17 15:50:25 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			istok_ampersand(t_lexer *lexer)
{
	return (lexer->line[lexer->i] == '&');
}

int			createtok_ampersand(t_lexer *lexer)
{
	t_token	tok;

	tok.size = sizeof(t_token);
	tok.type = T_AMPERSAND;
	if (!(tok.str = ft_strdup("&")))
		return (SH_ERR_MALLOC);
	tok.len = 1;
	return (token_process(lexer, &tok));
}
