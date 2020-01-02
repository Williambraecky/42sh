/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:42:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/02 19:25:23 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
** TODO: everything; this should build the current working tree
*/

/*
** NOTE: head is the starting command so result should always be head at the end
** TODO: define what to do when there are multiple
**    commands available in the lexer eg separated by ; or &
** TODO: define if cases exist where this is not the case
** NOTE: this will check for syntax errors eg incomplete redirections etc
**    and print the error if found
** NOTE: nothing in t_build should be freed
** NOTE: do we actually need shell for building the tree?
*/

/*
** TODO: for all these functions define a expected_type for the next one
*/

int		(*g_dispatch_tokens[])(t_token*, t_build*) =
{
	[T_NEWLINE] = apply_newline,
	[T_SEMICOLON] = apply_newline,
	[T_AMPERSAND] = apply_ampersand,
	[T_DOUBLE_AMPERSAND] = apply_dampersand,
	[T_DOUBLE_PIPE] = apply_dpipe,
	[T_PIPE] = apply_pipe,
	[T_WORD] = apply_word,
	[T_NULL] = NULL
};

int		build_tree(t_sh *shell, t_lexer *lexer, t_cmd **result)
{
	t_build	build;

	ft_memset(&build, 0, sizeof(build));
	if (cmd_new(&build.head))
		return (SH_ERR_MALLOC);
	build.work = build.head;
	if (proc_new(&build.work_proc))
	{
		free_tree(build.head);
		return (SH_ERR_MALLOC);
	}
	build.head->pipeline = build.work_proc;
	build.expected_type = M_WORD | M_SEMICOLON | M_NEWLINE
		| M_IO_NUMBER | M_ANY_REDIR;
	(void)shell;
	(void)lexer;
	*result = build.head;
	return (SH_SUCCESS);
}
