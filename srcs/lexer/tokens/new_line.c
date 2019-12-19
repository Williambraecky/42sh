/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:04:05 by ntom              #+#    #+#             */
/*   Updated: 2019/12/19 17:54:49 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			istok_newline(t_lexer *lexer, t_token *token)
{
	(void)lexer;
	return (token->str[0] == '\n');
}

int			transform_newline(t_lexer *lexer, t_token *token)
{
	token->size = sizeof(t_token);
	token->type = T_NEWLINE;
	return (token_process(lexer, token));
}
