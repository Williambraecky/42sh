/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:22:45 by ntom              #+#    #+#             */
/*   Updated: 2019/11/13 17:59:34 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** ( ) (()) > < >> << >& <& && || { } ' " wspace word ; &> >&
*/

int		is_char_escaped(char *str, int index)
{
	if (!str || index == 0)
		return (0);
	return (str[index - 1] == '\\' && !is_char_escaped(str, index - 1));
}

size_t		get_next_token(t_lexer lexer)
{
	//while ((t_token*)ft_vecget(&lexer->tokens, lexer.i)->type != WORD);
	return (0);
}

t_lexer		tokenization(char *line)
{
	size_t		i;
	size_t		ret;
	t_lexer		lexer;

	i = 0;
	ret = 0;
	while (get_next_token(lexer))
	{

	}
	return (lexer);
}
