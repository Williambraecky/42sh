/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_greater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:25:49 by ntom              #+#    #+#             */
/*   Updated: 2019/12/17 15:54:18 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int				istok_double_greater(t_lexer *lexer)
{
	return (lexer->line[lexer->i] == '>' && lexer->line[lexer->i + 1] == '>');
}

int				createtok_double_greater(t_lexer *lexer)
{
	t_token	tok;

	tok.size = sizeof(t_token);
	tok.type = T_DOUBLE_GREATER;
	if (!(tok.str = ft_strdup(">>")))
		return (SH_ERR_MALLOC);
	tok.len = 2;
	return (token_process(lexer, &tok));
}
