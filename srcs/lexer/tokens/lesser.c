/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lesser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:21:40 by ntom              #+#    #+#             */
/*   Updated: 2019/11/15 15:22:35 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		istok_lesser(t_lexer *lexer)
{
	size_t	i;
	char	*str;
	int		num_first;
	int		greater_first;

	i = lexer->i;
	str = lexer->line;
	num_first = 0;
	greater_first = 0;
	if (is_char_escaped(lexer->line, lexer->i))
		return (0);
	if (isdigit(str[i]))
		num_first = 1;
	else if (str[i] == '<')
		greater_first = 1;
	i++;
	if ((!(str) && greater_first == 1)
		|| (isdigit(str[i]) && greater_first == 1)
		|| (str[i] == '<' && num_first == 1)
		|| ((str[i] == '<' && num_first == 1
			&& str[i + 1] && isdigit(str[i + 1]))))
		return (1);
	return (0);
}
