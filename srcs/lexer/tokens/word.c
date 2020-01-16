/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:15:50 by ntom              #+#    #+#             */
/*   Updated: 2020/01/16 01:15:35 by wbraeckm         ###   ########.fr       */
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
	if (token->len == 1 &&
		(token->str[0] == ' ' || token->str[0] == '\t'))
	{
		free(token->str);
		return (SH_SUCCESS);
	}
	token->type = T_WORD;
	token->size = sizeof(*token);
	return (token_process(lexer, token));
}
