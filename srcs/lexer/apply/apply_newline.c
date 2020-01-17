/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_newline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:32:25 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/17 16:20:43 by wbraeckm         ###   ########.fr       */
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

int			apply_newline(t_token *token, t_build *build, t_lexer *lexer)
{
	if (token->type == T_SEMICOLON || !proc_is_empty(build->work_proc))
		empty_stack(lexer);
	else if (token->type == T_NEWLINE && proc_is_empty(build->work_proc))
		return (SH_SUCCESS);
	if (cmd_new(&build->work->next))
		return (SH_ERR_MALLOC);
	build->work = build->work->next;
	if (proc_new(&build->work->pipeline))
		return (SH_ERR_MALLOC);
	build->work_proc = build->work->pipeline;
	build->work_proc->parent = build->work;
	lexer->can_be_alias = 1;
	alias_stack_clear(lexer);
	return (SH_SUCCESS);
}
