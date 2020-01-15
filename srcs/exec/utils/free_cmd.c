/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:20:20 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 17:21:47 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	free_pipeline(t_proc *pipeline)
{
	t_proc	*curr;

	curr = pipeline;
	while (curr)
	{
		ft_vecdestroy(&curr->unprocessed_argv, default_vec_destroy_function);
		ft_vecdestroy(&curr->redirections, default_vec_destroy_function);
		ft_vecdestroy(&curr->assignments, default_vec_destroy_function);
		if (curr->argv)
			ft_freesplit(curr->argv);
		if (curr->env)
			ft_freesplit(curr->env);
		ft_strdel(&curr->proc_str);
		pipeline = curr;
		curr = curr->next;
		free(pipeline);
	}
}

void		free_cmd(t_cmd *cmd)
{
	free_pipeline(cmd->pipeline);
	ft_strdel(&cmd->cmd_str);
	free(cmd);
}
