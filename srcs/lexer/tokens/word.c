/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:15:50 by ntom              #+#    #+#             */
/*   Updated: 2019/12/19 17:50:56 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			istok_word(t_lexer *lexer, t_token *token)
{
	(void)lexer;
	(void)token;
	return (1);
}

int			transform_word(t_lexer *lexer, t_token *token)
{
	t_word	tok;

	tok.token = *token;
	tok.token.type = T_WORD;
	tok.token.size = sizeof(t_word);
	tok.transformed = NULL;
	return (token_process(lexer, (t_token*)&tok));
}
