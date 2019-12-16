/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:41:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 13:59:10 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** TODO: dispatch token to correct function to build commands
*/

int		token_process(t_lexer *lexer, t_token *token)
{
	lexer->i += token->len;
	if (ft_veccpush(&lexer->tokens, token, token->size))
		return (SH_ERR_MALLOC);
	stack(token->type, &lexer->stack);
	return (SH_SUCCESS);
}
