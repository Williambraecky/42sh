/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:20:20 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/24 18:25:55 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	free_pipeline(t_proc *pipeline)
{
	t_proc	*curr;
	t_proc	*next;

	curr = pipeline;
	while (curr)
	{
		next = curr->next;
		free_proc(curr);
		curr = next;
	}
}

void		free_cmd(t_cmd *cmd)
{
	free_pipeline(cmd->pipeline);
	ft_strdel(&cmd->cmd_str);
	free(cmd);
}
