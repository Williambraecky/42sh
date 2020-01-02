/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 17:39:13 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/02 18:21:45 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		proc_new(t_proc **proc)
{
	if (!(*proc = ft_memalloc(sizeof(**proc))))
		return (SH_ERR_MALLOC);
	if (ft_vecinit(&((*proc)->unprocessed_argv))
		|| ft_vecinit(&((*proc)->redirections))
		|| ft_vecinit(&((*proc)->assignments)))
	{
		free(*proc);
		ft_vecfree(&((*proc)->unprocessed_argv));
		ft_vecfree(&((*proc)->redirections));
		ft_vecfree(&((*proc)->assignments));
		return (SH_ERR_MALLOC);
	}
	return (SH_SUCCESS);
}
