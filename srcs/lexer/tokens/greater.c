/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greater.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:08:07 by ntom              #+#    #+#             */
/*   Updated: 2019/11/22 15:08:57 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_valid_greater(char *str, int i)
{
	int		len;

	len = 0;
	if (isdigit(str[i]))
		len++;
	if (str[i + len] != '>')
		return (0);
	i++;
	if (isdigit(str[i + len]))
		len++;
	return (len);
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
