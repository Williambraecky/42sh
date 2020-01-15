/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:11:59 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 16:08:11 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** TODO: add new fields when added
** NOTE: since we copy the token and not the content
**    we don't need to free the tokens here
*/

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

/*
** NOTE: backgrounded cmds are freed by the job control
*/

void		free_tree(t_cmd *cmd)
{
	t_cmd	*curr;

	curr = cmd;
	while (curr)
	{
		if (curr->background == 0)
		{
			free_pipeline(curr->pipeline);
			ft_strdel(&cmd->cmd_str);
			cmd = curr;
			curr = curr->next;
			free(cmd);
		}
		else
			curr = curr->next;
	}
}
