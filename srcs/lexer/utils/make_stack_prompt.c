/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_stack_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:19:33 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/10 15:14:01 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*g_short_names[] =
{
	[T_BRACEPARAM] = "braceparam",
	[T_DOUBLE_QUOTE] = "dquote",
	[T_QUOTE] = "quote",
	[T_PIPE] = "pipe",
	[T_DOUBLE_PIPE] = "cmdor",
	[T_DOUBLE_AMPERSAND] = "cmdamd",
	[T_DOUBLE_LESSER] = "heredoc",
	[T_NULL] = ""
};

int		make_stack_prompt(t_vec *stack, char **result)
{
	char	**list;
	char	*tmp;
	t_type	*type;
	size_t	i;

	if (!(list = ft_memalloc(sizeof(*list) * (stack->size + 1))))
		return (SH_ERR_MALLOC);
	i = 0;
	while (i < stack->size)
	{
		type = (t_type*)ft_vecget(stack, i);
		if (g_short_names[*type])
			list[i] = g_short_names[*type];
		i++;
	}
	if (!(*result = ft_tabjoin(list, " ")))
		return (SH_ERR_MALLOC);
	if (!(tmp = ft_strjoin(*result, "> ")))
	{
		free(*result);
		return (SH_ERR_MALLOC);
	}
	free(*result);
	*result = tmp;
	return (SH_SUCCESS);
}
