/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:42:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/17 16:22:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_dquote_escaped(t_lexer *lex, size_t len)
{
	if (lex->line[len] == '$' ||
		lex->line[len] == '\"' ||
		lex->line[len] == '}')
		return (is_char_escaped(lex->line, len));
	return (1);
}

static int	g_sig_type = M_QUOTE | M_DOUBLE_QUOTE |
M_DOUBLE_LESSER | M_BRACEPARAM;

static int	stack_sig_top(t_lexer *lex)
{
	size_t	i;

	if (1 << stack_top(&lex->stack) & g_sig_type)
		return (stack_top(&lex->stack));
	i = lex->stack.size;
	while (i--)
	{
		if ((1 << (*(t_type*)lex->stack.vec[i])) & g_sig_type)
			return (*(t_type*)lex->stack.vec[i]);
	}
	return (T_NULL);
}

int			is_escaped(t_lexer *lex, size_t len)
{
	t_type	type;

	type = stack_sig_top(lex);
	if (type == T_QUOTE)
		return (lex->line[len] != '\'');
	else if (type == T_DOUBLE_QUOTE || type == T_BRACEPARAM)
		return (is_dquote_escaped(lex, len));
	else if (type == T_DOUBLE_LESSER)
		return (lex->line[len] != '\n');
	return (is_char_escaped(lex->line, len));
}

int			new_line_check(t_lexer *lex, size_t len)
{
	if (lex->line[len] != '\\' || lex->line[len + 1] != '\n')
		return (1);
	if (is_escaped(lex, len + 1) || stack_top(&lex->stack) == T_DOUBLE_LESSER)
	{
		ft_memmove(lex->line + len, lex->line + len + 2,
			ft_strlen(lex->line + len + 2) + 1);
	}
	if (!(lex->line[len]))
		stack_push(&lex->stack, T_NEWLINE);
	return (lex->line[len]);
}
