/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_stack_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:19:33 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/24 18:46:27 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*g_short_names[] =
{
	[T_BRACEPARAM] = "braceparam",
	[T_CMDSUBST] = "cmdsubst",
	[T_DOUBLE_QUOTE] = "dquote",
	[T_QUOTE] = "quote",
	[T_PIPE] = "pipe",
	[T_DOUBLE_PIPE] = "cmdor",
	[T_DOUBLE_AMPERSAND] = "cmdamd",
	[T_DOUBLE_LESSER] = "heredoc",
	[T_NULL] = ""
};

static void	fill_list(t_vec *stack, char **list)
{
	t_type	type;
	size_t	i;

	i = 0;
	while (i < stack->size)
	{
		type = (t_type)ft_vecget(stack, i);
		if (type != T_NULL && g_short_names[type])
			list[i] = g_short_names[type];
		i++;
	}
}

int			make_stack_prompt(t_vec *stack, char **result)
{
	char	**list;
	char	*tmp;

	if (!(list = ft_memalloc(sizeof(*list) * (stack->size + 1))))
		return (SH_ERR_MALLOC);
	fill_list(stack, list);
	if (!(*result = ft_tabjoin(list, " ")))
	{
		free(list);
		return (SH_ERR_MALLOC);
	}
	if (!(tmp = ft_strjoin(*result, "> ")))
	{
		free(list);
		free(*result);
		return (SH_ERR_MALLOC);
	}
	free(list);
	free(*result);
	*result = tmp;
	return (SH_SUCCESS);
}
