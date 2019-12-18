/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:42:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/18 18:07:20 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** NOTE: index is string is always len;
*/

static int	is_dquote_escaped(t_lexer *lex, size_t len)
{
	if (lex->line[len] == '$' || lex->line[len] == '\"')
		return (is_char_escaped(lex->line, len));
	return (1);
}

int			is_escaped(t_lexer *lex, size_t len)
{
	t_type	type;

	type = stack_top(lex);
	if (type == T_QUOTE)
		return (lex->line[len] != '\'');
	else if (type == T_DOUBLE_QUOTE)
		return (is_dquote_escaped(lex, len));
	return (is_char_escaped(lex->line, len));
}
