/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:42:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 02:16:03 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
** TODO: everything; this should build the current working tree
*/

/*
** NOTE: head is the starting command so result should always be head at the end
** NOTE: this will check for syntax errors eg incomplete redirections etc
**    and print the error if found
** NOTE: nothing in t_build should be freed
** NOTE: do we actually need shell for building the tree?
*/

/*
** TODO: for all these functions define a expected_type for the next one
** TODO: move expected type from
*/

int			(*g_dispatch_tokens[])(t_token*, t_build*) =
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

	[T_DOUBLE_AMPERSAND] = M_WORD | M_SEMICOLON | M_NEWLINE
	| M_DOUBLE_LESSER | M_DOUBLE_GREATER | M_LESSER_AND
	| M_GREATER_AND | M_GREATER | M_LESSER | M_IO_NUMBER,

	[T_DOUBLE_PIPE] = M_WORD | M_SEMICOLON | M_NEWLINE
	| M_DOUBLE_LESSER | M_DOUBLE_GREATER | M_LESSER_AND
	| M_GREATER_AND | M_GREATER | M_LESSER | M_IO_NUMBER,

	[T_PIPE] = M_WORD | M_SEMICOLON | M_NEWLINE
	| M_DOUBLE_LESSER | M_DOUBLE_GREATER | M_LESSER_AND
	| M_GREATER_AND | M_GREATER | M_LESSER | M_IO_NUMBER,

	[T_IO_NUMBER] = M_DOUBLE_LESSER | M_DOUBLE_GREATER | M_LESSER_AND
	| M_GREATER_AND | M_GREATER | M_LESSER,

	[T_DOUBLE_LESSER] = T_WORD,
	[T_DOUBLE_GREATER] = T_WORD,
	[T_LESSER] = T_WORD,
	[T_GREATER] = T_WORD,
	[T_LESSER_AND] = T_WORD,
	[T_GREATER_AND] = T_WORD,

	[T_WORD] = M_ANY,
	[T_NULL] = 0
};

static int	init_build_tree(t_build *build)
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

/*
** TODO: Newline doesn't always jump to the next command ex ls |\n cat -e
*/

int			build_tree(t_lexer *lexer, t_cmd **result)
{
	t_build	build;
	t_token	*curr;
	size_t	i;
	int		ret;

	if (init_build_tree(&build) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	i = 0;
	while (i < lexer->tokens.size)
	{
		curr = (t_token*)lexer->tokens.vec[i];
		if (g_dispatch_tokens[curr->type])
			ret = g_dispatch_tokens[curr->type](curr, &build);
		else
			ret = SH_ERR_NOEXIST;
		if (ret != SH_SUCCESS)
		{
			print_syntax_error(curr, ret);
			return (ret);
		}
		build.expected_type = g_expected[curr->type];
		i++;
	}
	*result = build.head;
	return (SH_SUCCESS);
}
