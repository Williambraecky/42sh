/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:32:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/19 17:54:53 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		istok_null(t_lexer *lexer, t_token *token)
{
	(void)lexer;
	return (token->str[0] == '\0');
}

int		transform_null(t_lexer *lexer, t_token *token)
{
	token->size = sizeof(t_token);
	token->type = T_NULL;
	return (token_process(lexer, token));
}
