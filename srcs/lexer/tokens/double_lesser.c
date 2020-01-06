/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_lesser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:15:45 by ntom              #+#    #+#             */
/*   Updated: 2020/01/06 18:39:37 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int				istok_double_lesser(t_lexer *lexer, t_token *token)
{
	(void)lexer;
	return (token->str[0] == '<' && token->str[1] == '<');
}

int				transform_double_lesser(t_lexer *lexer, t_token *token)
{
	t_hdoc	doc;

	ft_memset(&doc, 0, sizeof(doc));
	token->size = sizeof(doc);
	token->type = T_DOUBLE_LESSER;
	doc.token = *token;
	return (token_process(lexer, (t_token*)&doc));
}
