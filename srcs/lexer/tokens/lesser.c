/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lesser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:21:40 by ntom              #+#    #+#             */
/*   Updated: 2019/11/20 22:56:22 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_valid_lesser(char *str, int i)
{
	int		num_first;
	int		lesser_first;

	num_first = 0;
	lesser_first = 0;
	if (isdigit(str[i]))
		num_first = 1;
	else if (str[i] == '<')
		lesser_first = 1;
	i++;
	if (!(str) && lesser_first == 1)
		return (1);
	if ((isdigit(str[i]) && lesser_first == 1)
		|| (str[i] == '<' && num_first == 1))
		return (2);
	if ((str[i] == '<' && num_first == 1
			&& str[i + 1] && isdigit(str[i + 1])))
		return (3);
	return (0);
}

int			istok_lesser(t_lexer *lexer)
{
	size_t	i;
	char	*str;

	i = lexer->i;
	str = lexer->line;
	if (is_valid_lesser(lexer->line, lexer->i))
		return (1);
	return (0);
}

int			createtok_lesser(t_lexer *lexer)
{
	t_token	tok;
	int		len;
	char	*tmp;

	len = is_valid_lesser(lexer->line, lexer->i);
	tmp = lexer->line + lexer->i;
	tok.size = sizeof(t_token);
	tok.type = T_LESSER;
	if (!(tok.str = ft_strndup(tmp, len)))
		return (SH_ERR_MALLOC);
	tok.len = len;
	token_process(lexer, &tok);
	return (SH_SUCCESS);
}
