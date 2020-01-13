/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_is_stopped.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 00:53:36 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 01:14:41 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		job_is_stopped(t_cmd *cmd)
{
	t_proc *curr;

	curr = cmd->pipeline;
	while (curr)
	{
		if (!curr->completed && !curr->stopped)
			return (0);
		curr = curr->next;
	}
	return (1);
}
