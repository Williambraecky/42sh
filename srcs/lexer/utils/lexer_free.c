/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:59:02 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/14 00:01:26 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** NOTE: add new fields to be freed
*/

void	lexer_free(t_lexer *lexer)
{
	if (lexer->tokens.vec)
		ft_vecdestroy(&lexer->tokens, token_free);
	free(lexer->alias_stack);
	ft_strdel(&lexer->line);
	if (lexer->stack.vec)
		ft_vecdestroy(&lexer->stack, default_vec_destroy_function);
}
