/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greaterand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:46:46 by ntom              #+#    #+#             */
/*   Updated: 2019/12/26 21:50:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			istok_greaterand(t_lexer *lexer, t_token *token)
{
	(void)lexer;
	if ((token->str[0] == '>' && token->str[1] == '&') ||
		(token->str[0] == '&' && token->str[1] == '>'))
		return (1);
	return (0);
}

int			transform_greaterand(t_lexer *lexer, t_token *token)
{
	token->size = sizeof(t_token);
	token->type = T_GREATER_AND;
	return (token_process(lexer, token));
}
