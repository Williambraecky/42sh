/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_ampersand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:39:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/02 18:48:18 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		apply_ampersand(t_token *token, t_build *build)
{
	(void)token;
	if (build->expected_type && !(build->expected_type & (1 << token->type)))
		return (SH_ERR_SYNTAX);
	build->work->background = 1;
	if (cmd_new(&build->work->next))
		return (SH_ERR_MALLOC);
	build->work = build->work->next;
	if (proc_new(&build->work->pipeline))
		return (SH_ERR_MALLOC);
	build->work_proc = build->work->pipeline;
	return (SH_SUCCESS);
}
