/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 17:51:08 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/08 17:52:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		backup_fds(t_sh *shell)
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		if ((shell->fd_backups[i] = dup(i)) == -1)
			return (SH_ERR_DUP);
		i++;
	}
	return (SH_SUCCESS);
}
