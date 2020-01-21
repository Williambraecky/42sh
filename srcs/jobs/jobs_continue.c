/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_continue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 01:08:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 21:38:17 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	unflag_stopped(t_cmd *cmd)
{
	t_proc *curr;

	curr = cmd->pipeline;
	while (curr)
	{
		curr->stopped = 0;
		curr = curr->next;
	}
	cmd->notified = 0;
}

void		job_continue(t_sh *shell, t_cmd *cmd, int fg)
{
	unflag_stopped(cmd);
	if (fg)
		jobs_to_foreground(shell, cmd, 1);
	else
		jobs_to_background(shell, cmd, 1);
}
