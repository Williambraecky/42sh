/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:11:59 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/02 18:27:02 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		while (curr->argv && curr->argc--)
			free(curr->argv[curr->argc]);
		free(curr->argv);
		ft_vecdestroy(&curr->unprocessed_argv, default_vec_destroy_function);
		ft_vecdestroy(&curr->redirections, default_vec_destroy_function);
		ft_vecdestroy(&curr->assignments, default_vec_destroy_function);
		pipeline = curr;
		curr = curr->next;
		free(pipeline);
	}
}

void		free_tree(t_cmd *cmd)
{
	t_cmd	*curr;

	curr = cmd;
	while (curr)
	{
		free_pipeline(curr->pipeline);
		cmd = curr;
		curr = curr->next;
		free(cmd);
	}
}
