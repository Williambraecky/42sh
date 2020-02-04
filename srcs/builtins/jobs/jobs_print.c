/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 00:12:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/22 00:13:12 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"

void		print_lflag(t_cmd *cmd, size_t index, size_t max)
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
		ft_printf("%d %-10s %s\n", curr->pid, get_signal_str(curr),
			curr->proc_str);
		curr = curr->next;
	}
}

void		print_pflag(t_cmd *cmd, size_t index, size_t max)
{
	t_proc	*curr;
	size_t	len;

	len = ft_intlen(index);
	curr = cmd->pipeline;
	while (curr)
	{
		if (curr == cmd->pipeline)
		{
			if (index == max)
				ft_printf("[%zu]  + ", index);
			else
				ft_printf("[%zu]  %s ", index == max - 1 ? "-" : " ");
		}
		else
			ft_printf("%*s    ", len + 2, "");
		if (curr == cmd->pipeline)
			ft_printf("%d %-*s %s\n", curr->pid, 10, get_signal_str(curr),
				curr->proc_str);
		else
			ft_printf("%*s %-*s %s\n", ft_intlen(cmd->pipeline->pid), "", 10,
				get_signal_str(curr), curr->proc_str);
		curr = curr->next;
	}
}

void		basic_print(t_cmd *cmd, size_t index, size_t max)
{
	t_proc	*curr;
	t_proc	*last;
	size_t	len;

	len = ft_intlen(index);
	curr = cmd->pipeline;
	ft_printf("[%zu] ", index);
	if (index == max)
		ft_printf(" + ");
	else if (index == max - 1)
		ft_printf(" - ");
	else
		ft_printf("   ");
	last = cmd->pipeline;
	while (last->next)
		last = last->next;
	ft_printf("%-*s %s\n", 10, get_signal_str(last), cmd->cmd_str);
}
