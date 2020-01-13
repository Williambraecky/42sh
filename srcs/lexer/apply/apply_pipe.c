/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:56:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 18:10:50 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		apply_pipe(t_token *token, t_build *build)
{
	(void)token;
	if (proc_new(&build->work_proc->next))
		return (SH_ERR_MALLOC);
	build->work_proc = build->work_proc->next;
	build->work_proc->parent = build->work;
	return (SH_SUCCESS);
}
