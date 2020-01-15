/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_signal_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:39:38 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 19:06:07 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: status is the return from wait
*/

char	*get_signal_str(int status)
{
	(void)status;
	if (WIFSTOPPED(status))
	{
		if (WSTOPSIG(status) == SIGTSTP)
			return ("suspended");
		return ("stopped");
	}
	else if (WIFSIGNALED(status))
		return ("killed");
	return ("temp");
}
