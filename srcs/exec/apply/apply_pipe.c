/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:56:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/02 18:58:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		apply_pipe(t_token *token, t_build *build)
{
	(void)token;
	if (build->expected_type && !(build->expected_type & (1 << token->type)))
		return (SH_ERR_SYNTAX);
	if (proc_new(&build->work_proc->next))
		return (SH_ERR_MALLOC);
	build->work_proc = build->work_proc->next;
	return (SH_SUCCESS);
}
