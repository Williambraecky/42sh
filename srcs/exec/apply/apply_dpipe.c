/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_dpipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:49:13 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/02 18:49:42 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		apply_dpipe(t_token *token, t_build *build)
{
	(void)token;
	if (build->expected_type && !(build->expected_type & (1 << token->type)))
		return (SH_ERR_SYNTAX);
	if (cmd_new(&build->work->next))
		return (SH_ERR_MALLOC);
	build->work = build->work->next;
	build->work->condition = or_condition;
	if (proc_new(&build->work->pipeline))
		return (SH_ERR_MALLOC);
	build->work_proc = build->work->pipeline;
	return (SH_SUCCESS);
}