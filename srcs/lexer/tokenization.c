/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:22:45 by ntom              #+#    #+#             */
/*   Updated: 2020/01/28 14:43:12 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "prompt.h"

t_tdef		g_def_table[] =
{
	{T_NEWLINE, istok_newline, transform_newline},
	{T_DOUBLE_AMPERSAND, istok_double_ampersand, transform_double_ampersand},
	{T_DOUBLE_PIPE, istok_double_pipe, transform_double_pipe},
	{T_DOUBLE_LESSER, istok_double_lesser, transform_double_lesser},
	{T_DOUBLE_GREATER, istok_double_greater, transform_double_greater},
	{T_LESSER_AND, istok_lesserand, transform_lesserand},
	{T_GREATER_AND, istok_greaterand, transform_greaterand},
	{T_LESSER, istok_lesser, transform_lesser},
	{T_GREATER, istok_greater, transform_greater},
	{T_PIPE, istok_pipe, transform_pipe},
	{T_SEMICOLON, istok_semicolon, transform_semicolon},
	{T_AMPERSAND, istok_ampersand, transform_ampersand},
	{T_IO_NUMBER, istok_io_number, transform_io_number},
	{T_WORD, istok_word, transform_word},
	{T_NULL, istok_null, transform_null}
};

size_t		g_size = sizeof(g_def_table) / sizeof(*g_def_table);

t_tdef		*determine_type(t_lexer *lexer, t_token *token)
{
	size_t	i;

	i = 0;
	while (i < g_size)
	{
		if (g_def_table[i].is_tok(lexer, token))
			return (&g_def_table[i]);
		i++;
	}
	return (NULL);
}

static int	g_top_mask =
M_QUOTE | M_DOUBLE_QUOTE | M_BRACEPARAM | M_NEWLINE | M_CMDSUBST;

/*
** NOTE: returns whether a stack object from delimiter
**    is at the top of the stack
*/

static int	check_stack_top(t_lexer *lexer)
{
	if ((1 << stack_top(&lexer->stack)) & g_top_mask)
		return (1);
	return (0);
}

/*
** NOTE: don't forget prompt can return ctrl + c
*/

static int	get_next_part(t_lexer *lexer, t_sh *shell)
{
	char	*line;
	char	*tmp;
	int		ret;

	if ((ret = make_stack_prompt(&lexer->stack, &tmp)) != SH_SUCCESS)
		return (ret);
	if ((ret = handle_prompt(shell, tmp, &line)) != SH_SUCCESS)
	{
		free(tmp);
		return (ret);
	}
	free(tmp);
	tmp = lexer->line;
	if (!(lexer->line = ft_strjoin(lexer->line, line)))
		ret = SH_ERR_MALLOC;
	ft_strdel(&tmp);
	tmp = lexer->clean_line;
	if (!(lexer->clean_line = ft_strjoin(lexer->clean_line, line)))
		ret = SH_ERR_MALLOC;
	ft_strdel(&tmp);
	lexer->line_size += ft_strlen(line);
	ft_strdel(&line);
	while (check_stack_top(lexer))
		stack_pop(&lexer->stack);
	return (ret);
}

static void	tokenize_current(t_lexer *lexer, t_sh *shell, int *res)
{
	t_tdef	*new_tok_def;
	t_token	tok;

	while (lexer->line[lexer->i] && *res == SH_SUCCESS)
	{
		if ((*res = delimit_token(lexer, &tok.str)) != SH_SUCCESS)
			return ;
		if (check_stack_top(lexer) || (tok.len = ft_strlen(tok.str)) == 0)
		{
			free(tok.str);
			break ;
		}
		if (lexer->can_be_alias && has_alias(shell, tok.str) &&
			!alias_stack_contains(lexer, tok.str))
		{
			*res = lexer_handle_alias(shell, lexer, tok.str);
			continue ;
		}
		if (!(new_tok_def = determine_type(lexer, &tok)))
			*res = SH_ERR_NOEXIST;
		if (*res == SH_SUCCESS &&
			(*res = new_tok_def->transform(lexer, &tok)) != SH_SUCCESS)
			return ;
		lexer->i += tok.len;
	}
}

int			tokenization(t_lexer *lexer, t_sh *shell)
{
	int		res;

	res = SH_SUCCESS;
	while (res == SH_SUCCESS)
	{
		tokenize_current(lexer, shell, &res);
		if (res == SH_SUCCESS && lexer->stack.size > 0)
			res = get_next_part(lexer, shell);
		else
			break ;
	}
	return (res);
}
