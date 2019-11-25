/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lesser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:21:40 by ntom              #+#    #+#             */
/*   Updated: 2019/11/25 15:26:19 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static size_t	is_valid_lesser(char *str, size_t i)
{
	size_t		len;

	len = 0;
	if (isdigit(str[i]))
		len++;
	if (str[i + len] != '<')
		return (0);
	i++;
	if (isdigit(str[i + len]))
		len++;
	return (len);
}

int				istok_lesser(t_lexer *lexer)
{
	size_t	i;
	char	*str;

	i = lexer->i;
	str = lexer->line;
	if (is_valid_lesser(lexer->line, lexer->i))
		return (1);
	return (0);
}

int				createtok_lesser(t_lexer *lexer)
{
	t_token	tok;
	size_t	len;
	char	*tmp;

	len = is_valid_lesser(lexer->line, lexer->i);
	tmp = lexer->line + lexer->i;
	tok.size = sizeof(t_token);
	tok.type = T_LESSER;
	if (!(tok.str = ft_strndup(tmp, len)))
		return (SH_ERR_MALLOC);
	tok.len = len;
	return (token_process(lexer, &tok));
}
