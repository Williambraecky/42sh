/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_ampersand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:39:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/18 15:56:03 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	empty_stack(t_lexer *lexer)
{
	t_type top;

	top = stack_top(&lexer->stack);
	while (top == T_PIPE ||
		top == T_DOUBLE_PIPE ||
		top == T_DOUBLE_AMPERSAND)
	{
		stack_pop(&lexer->stack);
		top = stack_top(&lexer->stack);
	}
}

int			apply_ampersand(t_token *token, t_build *build, t_lexer *lexer)
{
	(void)token;
	empty_stack(lexer);
	build->work->background = 1;
	if (cmd_new(&build->work->next))
		return (SH_ERR_MALLOC);
	build->work = build->work->next;
	if (proc_new(&build->work->pipeline))
		return (SH_ERR_MALLOC);
	build->work_proc = build->work->pipeline;
	build->work_proc->parent = build->work;
	build->work_proc->block_sigtstp = lexer->block_sigtstp;
	lexer->can_be_alias = 1;
	alias_stack_clear(lexer);
	return (SH_SUCCESS);
}
