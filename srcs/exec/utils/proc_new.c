/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 17:39:13 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 18:02:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		proc_new(t_proc **proc)
{
	size_t	i;

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
	i = PROC_FD_BACKUP_SIZE;
	while (i--)
		(*proc)->fd_backups[i] = -1;
	return (SH_SUCCESS);
}
