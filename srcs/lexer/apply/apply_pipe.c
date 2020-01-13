/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:56:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 22:54:52 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		apply_pipe(t_token *token, t_build *build, t_lexer *lexer)
{
	if (proc_new(&build->work_proc->next))
		return (SH_ERR_MALLOC);
	build->work_proc = build->work_proc->next;
	build->work_proc->parent = build->work;
	if (stack_push(lexer, token->type) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	lexer->can_be_alias = 1;
	return (SH_SUCCESS);
}
