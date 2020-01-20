/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:35:38 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 00:49:15 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void		job_notify_cmd(t_cmd *cmd, size_t index, size_t max)
{
	t_proc	*curr;
	size_t	len;

	len = ft_intlen(index);
	curr = cmd->pipeline;
	while (curr)
	{
		if (curr == cmd->pipeline)
		{
			ft_printf("[%zu] ", index);
			if (index == max)
				ft_printf(" + ");
			else if (index == max - 1)
				ft_printf(" - ");
			else
				ft_printf("   ");
		}
		else
			ft_printf("%*s    ", len + 2, "");
		ft_printf("%d %-*s(%d) %s\n", curr->pid, 10,
			get_signal_str(curr), curr->status, curr->proc_str);
		curr = curr->next;
	}
}

void		job_notify(t_sh *shell)
{
	size_t	i;
	size_t	j;
	t_cmd	*curr;
	size_t	max;

	i = 0;
	j = 0;
	max = shell->jobs.size;
	jobs_update_status(shell);
	while (i < shell->jobs.size && ++j)
	{
		curr = (t_cmd*)ft_vecget(&shell->jobs, i++);
		if (job_is_completed(curr))
		{
			job_notify_cmd(curr, j, max);
			ft_vecdel(&shell->jobs, --i); //TODO: free cmd
			free_cmd(curr);
			continue ;
		}
		else if (job_is_stopped(curr) && !curr->notified)
		{
			job_notify_cmd(curr, i, shell->jobs.size);
			curr->notified = 1;
		}
	}
}
