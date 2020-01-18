/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 21:07:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/18 14:24:37 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"
// if (!*str || ft_isdigit(*str))
// 	return (0);
// while (*str)
// {
// 	if (!(ft_isalnum(*str) || *str == '_'))
// 		return (0);
// 	str++;
// }
// return (1);

/*
** NOTE: special rule if it starts with an out of set character
**    if it exists it shall be substituted
*/

/*
** NOTE: start doesn't point to the $
*/

static int		var_exists(t_subst *subst, size_t start)
{
	char	buffer[2];

	buffer[0] = subst->str[start];
	buffer[1] = '\0';
	return (has_internal(subst->shell, buffer) ||
		has_env(subst->shell, buffer));
}

static size_t	count_characters(t_subst *subst, size_t start)
{
	size_t	end;

	end = start;
	if (subst->str[end] == '\0')
		return (0);
	while (subst->str[end])
	{
		if (end == start && !ft_isalpha(subst->str[end]) &&
			subst->str[end] != '_')
			break ;
		else if (!ft_isalnum(subst->str[end]) && subst->str[end] != '_')
			break ;
		end++;
	}
	if (start == end && var_exists(subst, start))
		return (1);
	return (end - start);
}

void			substitute_param(t_subst *subst)
{
	char	*tmp;
	char	*var;
	size_t	j;

	if (subst->str[subst->i + 1] == '{')
		return (substitute_parambrace(subst));
	else if (subst->str[subst->i + 1] == '(')
		return (substitute_cmd(subst));
	subst->i++;
	if ((j = count_characters(subst, subst->i)) == 0)
	{
		subst->err = buff_append(&subst->buffer, "$");
		return ;
	}
	if (!(tmp = ft_strndup(subst->str + subst->i, j)))
	{
		subst->err = SH_ERR_MALLOC;
		return ;
	}
	if (get_internal(subst->shell, tmp, &var) != SH_SUCCESS &&
		get_env(subst->shell, tmp, &var) != SH_SUCCESS)
		var = "";
	subst->err = buff_append(&subst->buffer, var);
	subst->i += j;
	free(tmp);
}
