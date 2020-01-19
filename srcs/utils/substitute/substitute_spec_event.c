/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_spec_event.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 16:26:50 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/19 17:14:33 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static size_t	count_characters(t_subst *subst, size_t start)
{
	size_t		end;

	end = start + 1;
	if (subst->str[end] == ' ' || subst->str[end] == '\t' ||
		subst->str[end] == '\0' || subst->str[end] == '=' ||
		subst->str[end] == '(')
		return (end - start);
	if (subst->str[end] == '!')
		return (end - start + 1);
	while (subst->str[end] &&
		(ft_isalnum(subst->str[end]) || subst->str[end] == '-'))
		end++;
	return (end - start);
}

static void		handle_via_query(t_subst *subst, char *tmp, char **append)
{
	size_t		index;
	char		*histo;

	index = subst->shell->history.size;
	histo = NULL;
	while (index--)
	{
		if (ft_strstartswith_ncs(subst->shell->history.vec[index], tmp + 1))
		{
			histo = subst->shell->history.vec[index];
			break ;
		}
	}
	if (!histo)
	{
		ft_dprintf(2, "42sh: event not found: %s\n", tmp + 1);
		subst->err = SH_ERR_NOEVENT;
		return ;
	}
	if (!(*append = ft_strdup(histo)))
		subst->err = SH_ERR_MALLOC;
}

static void		handle_via_index(t_subst *subst, char *tmp, char **append)
{
	int		index;
	size_t	real_index;
	char	*histo;

	index = ft_atoi(tmp + 1);
	if (tmp[1] == '!')
		real_index = subst->shell->history.size - 1;
	else if (index > 0)
		real_index = (size_t)index - 1;
	else if (index < 0 && (int)subst->shell->history.size >= index)
		real_index = subst->shell->history.size + index;
	else
		real_index = 0;
	if (real_index >= subst->shell->history.size)
	{
		ft_dprintf(2, "42sh: no such event: %zu\n", real_index);
		subst->err = SH_ERR_NOEVENT;
		return ;
	}
	histo = (char*)ft_vecget(&subst->shell->history, real_index);
	if (!(*append = ft_strdup(histo)))
		subst->err = SH_ERR_MALLOC;
}

void			substitute_spec_event(t_subst *subst)
{
	char		*tmp;
	char		*append;
	size_t		j;

	if ((j = count_characters(subst, subst->i)) == 1)
	{
		subst->err = buff_append(&subst->buffer, "!");
		subst->i++;
		return ;
	}
	if (!(tmp = ft_strndup(subst->str + subst->i, j)))
	{
		subst->err = SH_ERR_MALLOC;
		return ;
	}
	append = NULL;
	if (tmp[1] == '!' || (ft_strisnumber(tmp + 1) && ft_atoi(tmp + 1) != 0))
		handle_via_index(subst, tmp, &append);
	else
		handle_via_query(subst, tmp, &append);
	if (subst->err == SH_SUCCESS && append)
		subst->err = buff_append(&subst->buffer, append);
	free(append);
	free(tmp);
	subst->i += j;
}
