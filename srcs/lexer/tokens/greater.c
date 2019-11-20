/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greater.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:08:07 by ntom              #+#    #+#             */
/*   Updated: 2019/11/20 22:56:57 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_valid_greater(char *str, int i)
{
	int		num_first;
	int		greater_first;

	num_first = 0;
	greater_first = 0;
	if (isdigit(str[i]))
		num_first = 1;
	else if (str[i] == '>')
		greater_first = 1;
	i++;
	if (!(str) && greater_first == 1)
		return (1);
	if ((isdigit(str[i]) && greater_first == 1)
		|| (str[i] == '>' && num_first == 1))
		return (2);
	if ((str[i] == '>' && num_first == 1
			&& str[i + 1] && isdigit(str[i + 1])))
		return (3);
	return (0);
}

int			istok_greater(t_lexer *lexer)
{
	size_t	i;
	char	*str;

	i = lexer->i;
	str = lexer->line;
	if (is_valid_greater(lexer->line, lexer->i))
		return (1);
	return (0);
}

int			createtok_greater(t_lexer *lexer)
{
	t_token	tok;
	int		len;
	char	*tmp;

	len = is_valid_greater(lexer->line, lexer->i);
	tmp = lexer->line + lexer->i;
	tok.size = sizeof(t_token);
	tok.type = T_GREATER;
	if (!(tok.str = ft_strndup(tmp, len)))
		return (SH_ERR_MALLOC);
	tok.len = len;
	token_process(lexer, &tok);
	return (SH_SUCCESS);
}
