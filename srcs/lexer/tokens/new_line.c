/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:04:05 by ntom              #+#    #+#             */
/*   Updated: 2019/11/20 17:43:30 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			is_newline_token(t_lexer *lexer)
{
	return (lexer->line[lexer->i] == '\n');
}

/*
** TODO: create and att token to lexer->tokens
*/

int			create_newline_token(t_lexer *lexer)
{
	t_token	tok;

	token_process(lexer, &tok);
	return (SH_SUCCESS);
}
