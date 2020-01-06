/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:31:51 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/06 14:49:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int		is_quoted(char *str, size_t i, t_type quote)
{
	if (quote == T_QUOTE)
		return (str[i] != '\'');
	else if (quote == T_DOUBLE_QUOTE)
		return (is_char_escaped(str, i) || str[i] == '\'');
	return (is_char_escaped(str, i));
}

static int		is_special_char(char *str, size_t i)
{
	return (str[i] == '\'' || str[i] == '\"' || str[i] == '\\');
}

static t_type	get_special_type(char *str, size_t i, t_type quote)
{
	if (str[i] == '\'')
		return (quote == T_QUOTE ? T_NULL : T_QUOTE);
	else if (str[i] == '\"')
		return (quote == T_DOUBLE_QUOTE ? T_NULL : T_DOUBLE_QUOTE);
	else if (str[i] == '\\')
		return (quote);
	return (T_NULL);
}

int				remove_quotes(char *str, char **result)
{
	size_t	i;
	size_t	j;
	char	*new;
	t_type	quote;

	quote = T_NULL;
	i = 0;
	j = 0;
	if (!(new = ft_memalloc(ft_strlen(str) + 1)))
		return (SH_ERR_MALLOC);
	while (str[i])
	{
		if (!is_quoted(str, i, quote) && is_special_char(str, i))
		{
			quote = get_special_type(str, i, quote);
			i++;
			continue ;
		}
		if (str[i])
			new[j++] = str[i++];
	}
	*result = new;
	return (SH_SUCCESS);
}
