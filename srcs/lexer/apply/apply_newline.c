/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_newline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:32:25 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 22:59:35 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** TODO: better solution for this problem as this is temporary
** TODO-NOTE: we might be able to use the stack for this
** NOTE: T_SEMICOLON also passes here, he however always create new cmd
*/

static int	g_no_new_cmd_mask = M_DOUBLE_PIPE | M_DOUBLE_AMPERSAND | M_PIPE;

static void	empty_stack(t_lexer *lexer)
{
	while (stack_top(lexer) == T_PIPE ||
		stack_top(lexer) == T_DOUBLE_PIPE ||
		stack_top(lexer) == T_DOUBLE_AMPERSAND)
		stack_pop(lexer);
}

int			apply_newline(t_token *token, t_build *build, t_lexer *lexer)
{
	if (token->type == T_SEMICOLON || !proc_is_empty(build->work_proc))
		empty_stack(lexer);
	if (g_no_new_cmd_mask & (1 << stack_top(lexer)) &&
		proc_is_empty(build->work_proc))
		return (SH_SUCCESS);
	if (cmd_new(&build->work->next))
		return (SH_ERR_MALLOC);
	build->work = build->work->next;
	if (proc_new(&build->work->pipeline))
		return (SH_ERR_MALLOC);
	build->work_proc = build->work->pipeline;
	build->work_proc->parent = build->work;
	lexer->can_be_alias = 1;
	return (SH_SUCCESS);
}
