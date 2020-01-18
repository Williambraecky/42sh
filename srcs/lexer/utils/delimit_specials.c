/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit_specials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:41:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/18 16:03:51 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char		*g_specials[] =
{
	"\\",
	"\"",
	"'",
	"${",
	"}",
	"$(",
	")",
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

static int	g_sig_type = M_QUOTE | M_DOUBLE_QUOTE |
M_DOUBLE_LESSER | M_BRACEPARAM | M_CMDSUBST;

int			delim_stack_sig_top(t_vec *stack)
{
	size_t	i;

	if (1 << stack_top(stack) & g_sig_type)
		return (stack_top(stack));
	i = stack->size;
	while (i--)
	{
		if ((1 << ((t_type)stack->vec[i])) & g_sig_type)
			return ((t_type)stack->vec[i]);
	}
	return (T_NULL);
}

static int	delim_handle_braceparam(t_vec *stack)
{
	if (delim_stack_sig_top(stack) == T_NULL)
	{
		ft_dprintf(2, "42sh: parse error near `}'\n");
		return (SH_ERR_PARSE);
	}
	else if (stack_top(stack) == T_BRACEPARAM)
		stack_pop(stack);
	return (SH_SUCCESS);
}

static int	delim_handle_cmdsubst(t_vec *stack)
{
	if (delim_stack_sig_top(stack) == T_NULL)
	{
		ft_dprintf(2, "42sh: parse error near `)'\n");
		return (SH_ERR_PARSE);
	}
	else if (stack_top(stack) == T_CMDSUBST)
		stack_pop(stack);
	return (SH_SUCCESS);
}

int			delim_handle_specials(t_vec *stack, char *line, size_t len)
{
	size_t	i;

	i = match_special_character(line + len);
	if (ft_strequ(g_specials[i], "\""))
		return (stack_push_or_pop(stack, T_DOUBLE_QUOTE));
	else if (ft_strequ(g_specials[i], "'"))
		return (stack_push_or_pop(stack, T_QUOTE));
	else if (ft_strequ(g_specials[i], "${"))
		return (stack_push(stack, T_BRACEPARAM));
	else if (ft_strequ(g_specials[i], "$("))
		return (stack_push(stack, T_CMDSUBST));
	else if (ft_strequ(g_specials[i], "}"))
		return (delim_handle_braceparam(stack));
	else if (ft_strequ(g_specials[i], ")"))
		return (delim_handle_cmdsubst(stack));
	return (SH_SUCCESS);
}
