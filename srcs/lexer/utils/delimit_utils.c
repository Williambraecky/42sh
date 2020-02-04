/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:42:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/19 16:25:50 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_dquote_escaped(char *str, size_t len)
{
	if (str[len] == '$' ||
		str[len] == '\"' ||
		str[len] == '}' ||
		str[len] == ')' ||
		str[len] == '!' ||
		str[len] == '\\')
		return (is_char_escaped(str, len));
	return (1);
}

static int	is_bparam_escaped(char *str, size_t len)
{
	if (str[len] == '$' ||
		str[len] == '\"' ||
		str[len] == '\'' ||
		str[len] == '}' ||
		str[len] == '!' ||
		str[len] == '\\')
		return (is_char_escaped(str, len));
	return (1);
}

static int	is_cmdsubst_escaped(char *str, size_t len)
{
	if (str[len] == '$' ||
		str[len] == '\"' ||
		str[len] == '\'' ||
		str[len] == ')' ||
		str[len] == '!' ||
		str[len] == '\\')
		return (is_char_escaped(str, len));
	return (1);
}

int			is_escaped(t_vec *stack, char *str, size_t len)
{
	t_type	type;

	type = delim_stack_sig_top(stack);
	if (type == T_QUOTE)
		return (str[len] != '\'');
	else if (type == T_DOUBLE_QUOTE)
		return (is_dquote_escaped(str, len));
	else if (type == T_BRACEPARAM)
		return (is_bparam_escaped(str, len));
	else if (type == T_CMDSUBST)
		return (is_cmdsubst_escaped(str, len));
	else if (type == T_DOUBLE_LESSER)
		return (str[len] != '\n');
	return (is_char_escaped(str, len));
}

int			new_line_check(t_lexer *lex, size_t len)
{
	if (lex->line[len] != '\\' || lex->line[len + 1] != '\n')
		return (1);
	if (is_escaped(&lex->stack, lex->line, len + 1)
		|| stack_top(&lex->stack) == T_DOUBLE_LESSER)
	{
		ft_memmove(lex->line + len, lex->line + len + 2,
			ft_strlen(lex->line + len + 2) + 1);
	}
	if (!(lex->line[len]))
		stack_push(&lex->stack, T_NEWLINE);
	return (lex->line[len]);
}
