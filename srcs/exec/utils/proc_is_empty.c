/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_is_empty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:18:24 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/02 18:20:01 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		proc_is_empty(t_proc *proc)
{
	if (!proc)
		return (1);
	return (proc->unprocessed_argv.size == 0
		&& proc->redirections.size == 0
		&& proc->assignments.size == 0);
}
