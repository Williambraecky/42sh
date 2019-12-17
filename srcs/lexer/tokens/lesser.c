/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lesser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:21:40 by ntom              #+#    #+#             */
/*   Updated: 2019/12/17 15:53:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int				istok_lesser(t_lexer *lexer)
{
	return (lexer->line[lexer->i] == '<');
}

int				createtok_lesser(t_lexer *lexer)
{
	t_token	tok;

	tok.size = sizeof(t_token);
	tok.type = T_LESSER;
	if (!(tok.str = ft_strdup("<")))
		return (SH_ERR_MALLOC);
	tok.len = 1;
	return (token_process(lexer, &tok));
}
