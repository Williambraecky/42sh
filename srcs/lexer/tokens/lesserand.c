/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lesserand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:20:55 by ntom              #+#    #+#             */
/*   Updated: 2019/11/15 15:21:23 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		istok_lesserand(t_lexer *lexer)
{
	if (is_char_escaped(lexer->line, lexer->i))
		return (0);
	if ((lexer->line[lexer->i] == '&' && lexer->line[lexer->i + 1] == '<')
		|| (lexer->line[lexer->i] == '<' && lexer->line[lexer->i + 1] == '&'))
		return (1);
	return (0);
}
