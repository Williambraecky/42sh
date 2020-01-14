/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:42:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/14 21:06:49 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** NOTE: head is the starting command so result should always be head at the end
** NOTE: this will check for syntax errors eg incomplete redirections etc
**    and print the error if found
** NOTE: nothing in t_build should be freed
** NOTE: do we actually need shell for building the tree?
*/

int			(*g_dispatch_tokens[])(t_token*, t_build*, t_lexer*) =
{
	[T_NEWLINE] = apply_newline,
	[T_SEMICOLON] = apply_newline,
	[T_AMPERSAND] = apply_ampersand,
	[T_DOUBLE_AMPERSAND] = apply_dampersand,
	[T_DOUBLE_PIPE] = apply_dpipe,
	[T_PIPE] = apply_pipe,
	[T_WORD] = apply_word,
	[T_IO_NUMBER] = apply_io_nb,
	[T_DOUBLE_LESSER] = apply_redir,
	[T_DOUBLE_GREATER] = apply_redir,
	[T_LESSER_AND] = apply_redir,
	[T_GREATER_AND] = apply_redir,
	[T_LESSER] = apply_redir,
	[T_GREATER] = apply_redir,
	[T_NULL] = NULL
};

int			g_expected[] =
{
	[T_NEWLINE] = M_WORD | M_SEMICOLON | M_NEWLINE
	| M_DOUBLE_LESSER | M_DOUBLE_GREATER | M_LESSER_AND
	| M_GREATER_AND | M_GREATER | M_LESSER | M_IO_NUMBER,

	[T_SEMICOLON] = M_WORD | M_SEMICOLON | M_NEWLINE
	| M_DOUBLE_LESSER | M_DOUBLE_GREATER | M_LESSER_AND
	| M_GREATER_AND | M_GREATER | M_LESSER | M_IO_NUMBER,

	[T_AMPERSAND] = M_WORD | M_SEMICOLON | M_NEWLINE
	| M_DOUBLE_LESSER | M_DOUBLE_GREATER | M_LESSER_AND
	| M_GREATER_AND | M_GREATER | M_LESSER | M_IO_NUMBER,

	[T_DOUBLE_AMPERSAND] = M_WORD | M_NEWLINE
	| M_DOUBLE_LESSER | M_DOUBLE_GREATER | M_LESSER_AND
	| M_GREATER_AND | M_GREATER | M_LESSER | M_IO_NUMBER,

	[T_DOUBLE_PIPE] = M_WORD | M_NEWLINE
	| M_DOUBLE_LESSER | M_DOUBLE_GREATER | M_LESSER_AND
	| M_GREATER_AND | M_GREATER | M_LESSER | M_IO_NUMBER,

	[T_PIPE] = M_WORD | M_NEWLINE
	| M_DOUBLE_LESSER | M_DOUBLE_GREATER | M_LESSER_AND
	| M_GREATER_AND | M_GREATER | M_LESSER | M_IO_NUMBER,

	[T_IO_NUMBER] = M_DOUBLE_LESSER | M_DOUBLE_GREATER | M_LESSER_AND
	| M_GREATER_AND | M_GREATER | M_LESSER,

	[T_DOUBLE_LESSER] = M_WORD,
	[T_DOUBLE_GREATER] = M_WORD,
	[T_LESSER] = M_WORD,
	[T_GREATER] = M_WORD,
	[T_LESSER_AND] = M_WORD,
	[T_GREATER_AND] = M_WORD,

	[T_WORD] = M_ANY,
	[T_NULL] = 0
};

int			init_build_tree(t_build *build)
{
	ft_memset(build, 0, sizeof(*build));
	if (cmd_new(&build->head))
		return (SH_ERR_MALLOC);
	build->work = build->head;
	if (proc_new(&build->work_proc))
	{
		free_tree(build->head);
		return (SH_ERR_MALLOC);
	}
	build->work_proc->parent = build->work;
	build->head->pipeline = build->work_proc;
	build->expected_type = M_WORD | M_SEMICOLON | M_NEWLINE
		| M_DOUBLE_LESSER | M_DOUBLE_GREATER | M_LESSER_AND
		| M_GREATER_AND | M_GREATER | M_LESSER | M_IO_NUMBER;
	build->prev_type = T_NULL;
	return (SH_SUCCESS);
}

static void	print_syntax_error(t_token *token, int ret)
{
	if (ret != SH_ERR_SYNTAX)
		return ;
	ft_dprintf(2, "42sh: syntax error near unexpected `");
	ft_putnonprint_fd(token->str, 2);
	ft_putstr_fd("'\n", 2);
}

int			build_tree_apply_token(t_lexer *lexer, t_token *token)
{
	int	ret;

	if (!(lexer->build.expected_type & (1 << token->type)))
		ret = SH_ERR_SYNTAX;
	else if (g_dispatch_tokens[token->type])
		ret = g_dispatch_tokens[token->type](token, &lexer->build, lexer);
	else
		ret = SH_ERR_NOEXIST;
	if (ret != SH_SUCCESS)
	{
		print_syntax_error(token, ret);
		return (ret);
	}
	lexer->build.expected_type = g_expected[token->type];
	lexer->build.prev_type = token->type;
	return (ret);
}
