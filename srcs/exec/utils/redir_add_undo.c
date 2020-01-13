/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_add_undo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:33:14 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 18:02:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		redir_add_undo(t_proc *proc, int fd)
{
	if (proc->fd_backups[fd] != -1)
		return (SH_SUCCESS);
	if (fd < PROC_FD_BACKUP_SIZE && (proc->fd_backups[fd] = dup(fd)) == -1)
		return (SH_ERR_DUP);
	return (SH_SUCCESS);
}
