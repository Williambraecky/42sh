/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_lesser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:15:45 by ntom              #+#    #+#             */
/*   Updated: 2019/11/22 15:16:23 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_valid_double_lesser(char *str, int i)
{
	int		len;

	len = 0;
	if (isdigit(str[i]))
		len++;
	if (ft_strncmp(str + (i + len), "<<", 2) != 0)
		return (0);
	len += 2;
	return (len);
}

int			istok_double_lesser(t_lexer *lexer)
{
	size_t	i;
	char	*str;

	i = lexer->i;
	str = lexer->line;
	if (is_valid_double_lesser(lexer->line, lexer->i))
		return (1);
	return (0);
}

int			createtok_double_lesser(t_lexer *lexer)
{
	t_token	tok;
	int		len;
	char	*tmp;

	len = is_valid_double_lesser(lexer->line, lexer->i);
	tmp = lexer->line + lexer->i;
	tok.size = sizeof(t_token);
	tok.type = T_DOUBLE_LESSER;
	if (!(tok.str = ft_strndup(tmp, len)))
		return (SH_ERR_MALLOC);
	tok.len = len;
	token_process(lexer, &tok);
	return (SH_SUCCESS);
}
