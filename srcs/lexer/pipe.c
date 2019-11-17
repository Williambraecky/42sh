/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:51:08 by ntom              #+#    #+#             */
/*   Updated: 2019/11/15 15:53:39 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		istok_pipe(t_lexer *lexer)
{
	if (is_char_escaped(lexer->line, lexer->i))
		return (0);
	if (lexer->line[lexer->i] == '|')
		return (1);
	return (0);
}
