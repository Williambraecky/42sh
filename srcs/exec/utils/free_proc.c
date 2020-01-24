/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:21:05 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/24 18:26:33 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	free_redir(t_redir *redir)
{
	free(redir->filename);
	free(redir);
}

void		free_proc(t_proc *proc)
{
	size_t	i;

	i = proc->unprocessed_argv.size;
	while (proc->argv && i--)
		free(proc->argv[i]);
	free(proc->argv);
	ft_vecdestroy(&proc->unprocessed_argv, default_vec_destroy_function);
	ft_vecdestroy(&proc->redirections, free_redir);
	ft_vecdestroy(&proc->assignments, default_vec_destroy_function);
	if (proc->env)
		ft_freesplit(proc->env);
	ft_strdel(&proc->proc_str);
	ft_strdel(&proc->path);
	ft_strdel(&proc->status_str);
	free(proc);
}
