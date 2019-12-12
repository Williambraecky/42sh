/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:41:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/09 20:50:01 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** TODO: dispatch token to correct function to build commands
*/

int		token_process(t_lexer *lexer, t_token *token)
{
	if (ft_veccpush(&lexer->tokens, token, token->size))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
