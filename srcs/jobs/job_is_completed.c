/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_is_completed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 00:58:08 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 00:58:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		job_is_completed(t_cmd *cmd)
{
	t_proc *curr;

	curr = cmd->pipeline;
	while (curr)
	{
		if (!curr->completed)
			return (0);
		curr = curr->next;
	}
	return (1);
}
