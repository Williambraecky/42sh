/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:55:58 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/23 16:36:00 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

int		jobs_add(t_sh *shell, t_cmd *cmd, int notify)
{
	t_proc	*curr;

	if (ft_vecpush(&shell->jobs, cmd))
		return (SH_ERR_MALLOC);
	if (!notify)
		return (SH_SUCCESS);
	ft_printf("[%zu] ", shell->jobs.size);
	curr = cmd->pipeline;
	while (curr)
	{
		ft_printf("%d", curr->pid);
		if (curr->next)
			ft_printf(" ");
		curr = curr->next;
	}
	ft_printf("\n");
	cmd->notified = 1;
	return (SH_SUCCESS);
}
