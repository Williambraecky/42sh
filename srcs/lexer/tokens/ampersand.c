/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ampersand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:06:46 by ntom              #+#    #+#             */
/*   Updated: 2019/11/20 22:51:32 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		istok_ampersand(t_lexer *lexer)
{
	if (lexer->line[lexer->i] == '&')
		return (1);
	return (0);
}

int			createtok_ampersand(t_lexer *lexer)
{
	t_token	tok;

	tok.size = sizeof(t_token);
	tok.type = T_AMPERSAND;
	if (!(tok.str = ft_strdup("&")))
		return (SH_ERR_MALLOC);
	tok.len = 1;
	token_process(lexer, &tok);
	return (SH_SUCCESS);
}
