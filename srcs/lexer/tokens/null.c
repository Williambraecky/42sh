/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:32:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/08 16:34:11 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		istok_null(t_lexer *lexer)
{
	return (lexer->line[lexer->i] == '\0');
}

int		createtok_null(t_lexer *lexer)
{
	t_token	tok;

	tok.size = sizeof(t_token);
	tok.type = T_NULL;
	if (!(tok.str = ft_strdup("")))
		return (SH_ERR_MALLOC);
	tok.len = 0;
	return (token_process(lexer, &tok));
}
