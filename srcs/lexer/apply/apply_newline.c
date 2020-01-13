/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_newline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:32:25 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 18:10:57 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** TODO: better solution for this problem as this is temporary
** TODO-NOTE: we might be able to use the stack for this
*/

static int	g_no_new_cmd_mask = M_DOUBLE_PIPE | M_DOUBLE_AMPERSAND | M_PIPE;

int			apply_newline(t_token *token, t_build *build)
{
	(void)token;
	if (g_no_new_cmd_mask & (1 << build->prev_type))
		return (SH_SUCCESS);
	if (cmd_new(&build->work->next))
		return (SH_ERR_MALLOC);
	build->work = build->work->next;
	if (proc_new(&build->work->pipeline))
		return (SH_ERR_MALLOC);
	build->work_proc = build->work->pipeline;
	build->work_proc->parent = build->work;
	return (SH_SUCCESS);
}
