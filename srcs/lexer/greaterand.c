/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greaterand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:46:46 by ntom              #+#    #+#             */
/*   Updated: 2019/11/14 20:07:37 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		istok_greaterand(t_lexer *lexer)
{
	if (is_char_escaped(lexer->line, lexer->i))
		return (0);
	if ((lexer->line[lexer->i] == '&' && lexer->line[lexer->i + 1] == '>')
		|| (lexer->line[lexer->i] == '>' && lexer->line[lexer->i + 1] == '&'))
		return (1);
	return (0);
}
