/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 21:07:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 22:30:52 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

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
	return (has_var(subst->shell, buffer));
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
	if (get_var(subst->shell, tmp, &var) != SH_SUCCESS)
		var = "";
	subst->err = buff_append(&subst->buffer, var);
	subst->i += j;
	free(tmp);
}
