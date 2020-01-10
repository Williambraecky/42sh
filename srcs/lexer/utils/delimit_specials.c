/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit_specials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:41:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/10 15:50:15 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern char	*g_specials[];

/*
** NOTE: this one returns the index in specials of the match
*/

static size_t	match_special_character(char *str)
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

static int		push_or_pop(t_lexer *lex, t_type type)
{
	t_type	type_2;

	type_2 = stack_top(lex);
	if (type != type_2)
		return (stack_push(lex, type));
	stack_pop(lex);
	return (SH_SUCCESS);
}

int				handle_specials(t_lexer *lex, size_t len)
{
	size_t	i;

	i = match_special_character(lex->line + len);
	if (ft_strequ(g_specials[i], "\""))
		return (push_or_pop(lex, T_DOUBLE_QUOTE));
	else if (ft_strequ(g_specials[i], "'"))
		return (push_or_pop(lex, T_QUOTE));
	else if (ft_strequ(g_specials[i], "${"))
		return (stack_push(lex, T_BRACEPARAM));
	else if (ft_strequ(g_specials[i], "}") && stack_top(lex) == T_BRACEPARAM)
		stack_pop(lex);
	return (SH_SUCCESS);
}
