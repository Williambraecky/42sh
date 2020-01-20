/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_signal_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:39:38 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 00:52:53 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

/*
** NOTE: status is the return from wait
*/

char	*get_signal_str(t_proc *proc)
{
	if (!proc->stopped && !proc->completed)
		return ("running");
	if (WIFSTOPPED(proc->status))
	{
		if (WSTOPSIG(proc->status) == SIGTSTP)
			return ("suspended");
		return ("stopped");
	}
	else if (WIFSIGNALED(proc->status))
		return ("killed");
	else if (WIFEXITED(proc->status))
		return ("Done");
	return ("temp");
}
