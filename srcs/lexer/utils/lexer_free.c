/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:59:02 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/17 22:47:21 by wbraeckm         ###   ########.fr       */
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
	ft_freesplit(lexer->alias_stack);
	ft_strdel(&lexer->clean_line);
	ft_strdel(&lexer->line);
	ft_vecfree(&lexer->stack);
}
