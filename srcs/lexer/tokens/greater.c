/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greater.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:08:07 by ntom              #+#    #+#             */
/*   Updated: 2019/11/15 15:22:23 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		istok_greater(t_lexer *lexer)
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
	else if (str[i] == '>')
		greater_first = 1;
	i++;
	if ((!(str) && greater_first == 1)
		|| (isdigit(str[i]) && greater_first == 1)
		|| (str[i] == '>' && num_first == 1)
		|| ((str[i] == '>' && num_first == 1
			&& str[i + 1] && isdigit(str[i + 1]))))
		return (1);
	return (0);
}
