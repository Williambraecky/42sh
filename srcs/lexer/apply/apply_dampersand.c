/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_dampersand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:45:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 22:45:50 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	empty_stack(t_lexer *lexer)
{
	while (stack_top(lexer) == T_PIPE)
		stack_pop(lexer);
}

int		apply_dampersand(t_token *token, t_build *build, t_lexer *lexer)
{
	if (cmd_new(&build->work->next))
		return (SH_ERR_MALLOC);
	build->work = build->work->next;
	build->work->condition = and_condition;
	if (proc_new(&build->work->pipeline))
		return (SH_ERR_MALLOC);
	build->work_proc = build->work->pipeline;
	build->work_proc->parent = build->work;
	empty_stack(lexer);
	if (stack_push(lexer, token->type) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
