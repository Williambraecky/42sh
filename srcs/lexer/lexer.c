/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:22:45 by ntom              #+#    #+#             */
/*   Updated: 2019/11/17 16:23:53 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** ( ) (()) { } wspace word >> <<
** ' " > <  >& <& | || &> >& & && ;
*/

size_t		get_next_token(t_lexer lexer)
{
	//while ((t_token*)ft_vecget(&lexer->tokens, lexer.i)->type != WORD);
	return (0);
}

void		init_lexer(t_lexer *lexer)
{
}

t_lexer		tokenization(char *line)
{
	size_t		i;
	size_t		ret;
	t_lexer		lexer;

	i = 0;
	ret = 0;
	init_lexer(&lexer);
	while (get_next_token(lexer))
	{

	}
	return (lexer);
}
