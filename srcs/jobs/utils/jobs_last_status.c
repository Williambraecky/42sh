/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_last_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:07:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 19:07:50 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		jobs_last_status(t_cmd *cmd)
{
	t_proc	*proc;

	proc = cmd->pipeline;
	while (proc->next)
		proc = proc->next;
	return (proc->status);
}
