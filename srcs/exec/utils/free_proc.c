/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:21:05 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 17:22:22 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_proc(t_proc *proc)
{
	ft_vecdestroy(&proc->unprocessed_argv, default_vec_destroy_function);
	ft_vecdestroy(&proc->redirections, default_vec_destroy_function);
	ft_vecdestroy(&proc->assignments, default_vec_destroy_function);
	if (proc->argv)
		ft_freesplit(proc->argv);
	if (proc->env)
		ft_freesplit(proc->env);
	ft_strdel(&proc->proc_str);
	free(proc);
}
