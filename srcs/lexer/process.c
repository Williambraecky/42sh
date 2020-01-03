/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:41:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/20 16:00:24 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** TODO: dispatch token to correct function to build commands
*/

extern char		*g_tab_types[];

static char *last_token_type(t_lexer *lexer)
{
	t_token *token;

	token = ft_vecgettop(&lexer->tokens);
	return (g_tab_types[token->type]);
}

int		token_process(t_lexer *lexer, t_token *token)
{
	if (ft_veccpush(&lexer->tokens, token, token->size))
		return (SH_ERR_MALLOC);
	ft_printf("Last token type %s, str %s\n", last_token_type(lexer), token->str); // to remove
	//stack(token->type, &lexer->stack); to remove?
	return (SH_SUCCESS);
}
