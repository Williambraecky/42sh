/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:51:08 by ntom              #+#    #+#             */
/*   Updated: 2019/11/20 22:48:18 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		istok_pipe(t_lexer *lexer)
{
	if (lexer->line[lexer->i] == '|')
		return (1);
	return (0);
}

int			createtok_pipe(t_lexer *lexer)
{
	t_token	tok;

	tok.size = sizeof(t_token);
	tok.type = T_PIPE;
	if (!(tok.str = ft_strdup("|")))
		return (SH_ERR_MALLOC);
	tok.len = 1;
	token_process(lexer, &tok);
	return (SH_SUCCESS);
}
