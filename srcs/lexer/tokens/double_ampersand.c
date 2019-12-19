/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_ampersand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:08:24 by ntom              #+#    #+#             */
/*   Updated: 2019/12/19 17:54:24 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			istok_double_ampersand(t_lexer *lexer, t_token *token)
{
	(void)lexer;
	return (token->str[0] == '&' && token->str[1] == '&');
}

int			transform_double_ampersand(t_lexer *lexer, t_token *token)
{
	token->size = sizeof(t_token);
	token->type = T_DOUBLE_AMPERSAND;
	return (token_process(lexer, token));
}
