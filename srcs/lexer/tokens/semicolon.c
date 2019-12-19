/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:04:53 by ntom              #+#    #+#             */
/*   Updated: 2019/12/19 17:54:57 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			istok_semicolon(t_lexer *lexer, t_token *token)
{
	(void)lexer;
	return (token->str[0] == ';' && token->str[1] == '\0');
}

int			transform_semicolon(t_lexer *lexer, t_token *token)
{
	token->size = sizeof(t_token);
	token->type = T_SEMICOLON;
	return (token_process(lexer, token));
}
