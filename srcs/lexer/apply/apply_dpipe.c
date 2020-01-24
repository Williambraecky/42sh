/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_dpipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:49:13 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/24 18:44:43 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	empty_stack(t_lexer *lexer)
{
	while (stack_top(&lexer->stack) == T_PIPE)
		stack_pop(&lexer->stack);
}

int			apply_dpipe(t_token *token, t_build *build, t_lexer *lexer)
{
	if (cmd_new(&build->work->next))
		return (SH_ERR_MALLOC);
	build->work = build->work->next;
	build->work->condition = or_condition;
	if (proc_new(&build->work->pipeline))
		return (SH_ERR_MALLOC);
	build->work_proc = build->work->pipeline;
	build->work_proc->parent = build->work;
	build->work_proc->block_sigtstp = lexer->block_sigtstp;
	empty_stack(lexer);
	if (stack_push(&lexer->stack, token->type) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	lexer->can_be_alias = 1;
	alias_stack_clear(lexer);
	return (SH_SUCCESS);
}
