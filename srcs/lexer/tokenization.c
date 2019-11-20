/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:22:45 by ntom              #+#    #+#             */
/*   Updated: 2019/11/20 15:17:59 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** ( ) (()) { } wspace word >> <<
** ' " > <  >& <& | || &> >& & && ;
*/

int			stock_token(t_lexer *lexer)
{
	if (lexer)
		;
	return (0);
}

int			is_token(t_lexer *lexer, int escaped)
{
	if (lexer || escaped)
		;
	return (0);
}

//while ((t_token*)ft_vecget(&lexer->tokens, lexer.i)->type != WORD);

int			get_next_token(t_lexer *lexer)
{
	int		escaped;

	escaped = is_char_escaped(lexer->line, lexer->i);
	if (is_token(lexer, escaped))
		return (stock_token(lexer));
	return (0);
}

t_lexer		*tokenization(t_lexer *lexer)
{
	size_t		ret;

	ret = 0;
	while (get_next_token(lexer))
	{
	}
	return (lexer);
}
