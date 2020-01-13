/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:41:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 22:47:03 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char			*g_tab_types[] =
{
	[T_NEWLINE] = "NEWLINE",
	[T_DOUBLE_AMPERSAND] = "DOUBLE_AMPERSAND",
	[T_DOUBLE_PIPE] = "DOUBLE_PIPE",
	[T_DOUBLE_LESSER] = "DOUBLE_LESSER",
	[T_DOUBLE_GREATER] = "DOUBLE_GREATER",
	[T_LESSER_AND] = "LESSER_AND",
	[T_GREATER_AND] = "GREATER_AND",
	[T_LESSER] = "LESSER",
	[T_GREATER] = "GREATER",
	[T_PIPE] = "PIPE",
	[T_QUOTE] = "QUOTE",
	[T_DOUBLE_QUOTE] = "DOUBLE_QUOTE",
	[T_SEMICOLON] = "SEMICOLON",
	[T_AMPERSAND] = "AMPERSAND",
	[T_WSPACE] = "WSPACE",
	[T_IO_NUMBER] = "IO_NUMBER",
	[T_WORD] = "WORD",
	[T_NULL] = "NULL"
};

int				g_stackable[] =
{
	[T_DOUBLE_PIPE] = 1,
	[T_DOUBLE_AMPERSAND] = 1,
	[T_PIPE] = 1,
	[T_NULL] = 0
};

static int		check_dless_exist(t_lexer *lex)
{
	size_t	i;
	t_token	*tok;

	i = 0;
	while (i < lex->tokens.size)
	{
		tok = (t_token*)ft_vecget(&lex->tokens, i);
		if ((tok->type == T_DOUBLE_LESSER) && ((t_hdoc*)tok)->completed == 0)
		{
			if ((i + 1) < lex->tokens.size
				&& ((t_token*)ft_vecget(&lex->tokens, i + 1))->type != T_WORD)
				return (SH_ERR_SYNTAX);
			if (remove_quotes(((t_token*)ft_vecget(&lex->tokens, i + 1))->str,
				&((t_hdoc*)tok)->name) != SH_SUCCESS)
				return (SH_ERR_MALLOC);
			if (pipe(((t_hdoc*)tok)->pipe) == -1)
				return (SH_ERR_PIPE);
			return (stack_push(lex, T_DOUBLE_LESSER));
		}
		i++;
	}
	return (SH_SUCCESS);
}

static t_hdoc	*find_heredoc(t_lexer *lex)
{
	size_t	i;
	t_token	*tok;

	i = 0;
	while (i < lex->tokens.size)
	{
		tok = (t_token*)ft_vecget(&lex->tokens, i);
		if ((tok->type == T_DOUBLE_LESSER) && ((t_hdoc*)tok)->completed == 0)
		{
			return ((t_hdoc*)tok);
		}
		i++;
	}
	return (NULL);
}

static int		do_heredoc(t_lexer *lex, t_token *tok)
{
	t_hdoc	*hdoc;

	hdoc = find_heredoc(lex);
	if (ft_strcmp(tok->str, hdoc->name) == 0)
	{
		close(hdoc->pipe[1]);
		hdoc->completed = 1;
		stack_pop(lex);
	}
	else
		ft_putstr_fd(tok->str, hdoc->pipe[1]);
	return (SH_SUCCESS);
}

int				token_process(t_lexer *lexer, t_token *token)
{
	t_token	*tok_dup;
	int		ret;

	ret = SH_SUCCESS;
	if (!(tok_dup = ft_memdup(token, token->size)))
		return (SH_ERR_MALLOC);
	if (stack_top(lexer) == T_DOUBLE_LESSER)
		do_heredoc(lexer, tok_dup);
	else
	{
		if (ft_vecpush(&lexer->tokens, tok_dup))
			return (SH_ERR_MALLOC);
		if (tok_dup->type == T_NEWLINE)
			ret = check_dless_exist(lexer);
		if (ret == SH_SUCCESS)
			ret = build_tree_apply_token(lexer, tok_dup);
	}
	return (ret);
}
