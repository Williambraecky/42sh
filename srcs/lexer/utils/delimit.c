/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:20:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/19 16:26:38 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** NOTE: main delimit procedure for token identification
** follows instructions from
** (https://pubs.opengroup.org/onlinepubs/007908799/xcu/chap2.html#tag_001_003)
*/

/*
** NOTE: `;' is not an operator but we still need to delimit it
*/

char	*g_operators[] =
{
	"&&",
	"||",
	"<<",
	">>",
	"<&",
	"&<",
	">&",
	"&>",
	";",
	NULL
};

char	*g_specials[] =
{
	"\\",
	"\"",
	"'",
	"${",
	"}",
	NULL
};

static int	match_operator(char *str)
{
	size_t	i;

	i = 0;
	while (g_operators[i])
	{
		if (ft_strstartswith(g_operators[i], str))
			return (1);
		i++;
	}
	return (0);
}

static int	match_special_character(char *str)
{
	size_t	i;

	i = 0;
	while (g_specials[i])
	{
		if (ft_strstartswith(g_specials[i], str))
			return (1);
		i++;
	}
	return (0);
}

static int	should_delimit(t_lexer *lex, size_t len,
	int operator, int curr_operator)
{
	int		escaped;

	escaped = is_escaped(lex, len);
	if (operator && !curr_operator)
		return (1);
	else if (curr_operator && lex->i + operator != len + 1)
		return (1);
	else if ((lex->line[len] == ' ' ||
		lex->line[len] == '\t') && !escaped)
		return (1);
	return (0);
}

int			delimit_wspace(t_lexer *lex, char **result)
{
	if (!(*result = ft_strndup(lex->line + lex->i, 1)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

/*
** NOTE: operator is a boolean defining if we found an operator or not
** TODO: \\n has a special behaviour
*/

int			delimit_token(t_lexer *lex, char **result)
{
	size_t	len;
	int		operator;
	int		curr_operator;

	len = lex->i;
	if (lex->line[len] && ft_strchr(" \t\n", lex->line[len]))
		return (delimit_wspace(lex, result));
	operator = 0;
	while (lex->line[len] && new_line_check(lex, len))
	{
		if (!is_escaped(lex, len) &&
			(curr_operator = match_operator(lex->line + len)))
			operator += 1;
		else
			curr_operator = 0;
		if (should_delimit(lex, len, operator, curr_operator))
			break ;
		if (!is_escaped(lex, len) && match_special_character(lex->line + len))
			if (handle_specials(lex, len) != SH_SUCCESS)
				return (SH_ERR_MALLOC);
		len++;
	}
	if (!(*result = ft_strndup(lex->line + lex->i, len - lex->i)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
