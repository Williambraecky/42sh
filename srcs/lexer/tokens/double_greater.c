/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_greater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:25:49 by ntom              #+#    #+#             */
/*   Updated: 2019/11/25 15:25:01 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static size_t	is_valid_double_greater(char *str, size_t i)
{
	size_t		len;

	len = 0;
	if (isdigit(str[i]))
		len++;
	if (ft_strncmp(str + (i + len), ">>", 2) != 0)
		return (0);
	len += 2;
	return (len);
}

int				istok_double_greater(t_lexer *lexer)
{
	size_t	i;
	char	*str;

	i = lexer->i;
	str = lexer->line;
	if (is_valid_double_greater(lexer->line, lexer->i))
		return (1);
	return (0);
}

int				createtok_double_greater(t_lexer *lexer)
{
	t_token	tok;
	size_t	len;
	char	*tmp;

	len = is_valid_double_greater(lexer->line, lexer->i);
	tmp = lexer->line + lexer->i;
	tok.size = sizeof(t_token);
	tok.type = T_DOUBLE_GREATER;
	if (!(tok.str = ft_strndup(tmp, len)))
		return (SH_ERR_MALLOC);
	tok.len = len;
	return (token_process(lexer, &tok));
}
