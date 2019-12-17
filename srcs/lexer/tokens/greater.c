/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greater.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:08:07 by ntom              #+#    #+#             */
/*   Updated: 2019/12/17 15:54:05 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int				istok_greater(t_lexer *lexer)
{
	return (lexer->line[lexer->i] == '>');
}

int				createtok_greater(t_lexer *lexer)
{
	t_token	tok;

	tok.size = sizeof(t_token);
	tok.type = T_GREATER;
	if (!(tok.str = ft_strdup(">")))
		return (SH_ERR_MALLOC);
	tok.len = 1;
	return (token_process(lexer, &tok));
}
