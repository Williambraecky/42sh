/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit_specials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:41:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/17 21:42:04 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*g_specials[] =
{
	"\\",
	"\"",
	"'",
	"${",
	"}",
	NULL
};

/*
** NOTE: this one returns the index in specials of the match
*/

int			match_special_character(char *str)
{
	size_t	i;

	i = 0;
	while (g_specials[i])
	{
		if (ft_strstartswith(str, g_specials[i]))
			return (i);
		i++;
	}
	return (0);
}

int				delim_handle_specials(t_vec *stack, char *line, size_t len)
{
	size_t	i;

	i = match_special_character(line + len);
	if (ft_strequ(g_specials[i], "\""))
		return (stack_push_or_pop(stack, T_DOUBLE_QUOTE));
	else if (ft_strequ(g_specials[i], "'"))
		return (stack_push_or_pop(stack, T_QUOTE));
	else if (ft_strequ(g_specials[i], "${"))
		return (stack_push(stack, T_BRACEPARAM));
	else if (ft_strequ(g_specials[i], "}") &&
		stack_top(stack) == T_BRACEPARAM)
		stack_pop(stack);
	return (SH_SUCCESS);
}
