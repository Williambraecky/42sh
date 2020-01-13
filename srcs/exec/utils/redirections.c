/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:51:10 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/12 23:37:23 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int			apply_dlesser_redir(t_proc *proc, t_redir *redir)
{
	int	redirected;
	int	fd;
	int	ret;

	redirected = redir_get_fd(redir);
	fd = ((t_hdoc*)redir->token)->pipe[0];
	if (fd == -1)
		return (SH_ERR_OPEN);
	if ((ret = redir_add_undo(proc, redirected)) != SH_SUCCESS)
		return (ret);
	close(redirected);
	if (dup2(fd, redirected) == -1)
	{
		close(fd);
		return (SH_ERR_DUP);
	}
	close(fd);
	return (SH_SUCCESS);
}

/*
** NOTE: word - is a special case, is closes the fd
*/

static int	redirand_get_fd(t_redir *redir)
{
	if (ft_strequ(redir->filename, "-"))
		return (0);
	if (ft_strisnumber(redir->filename) && ft_atoi(redir->filename) >= 0)
		return (ft_atoi(redir->filename));
	return (redir_open_file(redir->filename, redir->token->type));
}

static int	redirand_check_closed(t_proc *proc, int fd)
{
	size_t	i;
	int		new;

	i = PROC_FD_BACKUP_SIZE;
	while (i--)
	{
		if (proc->fd_backups[i] == fd)
		{
			if ((new = dup(proc->fd_backups[i])) == -1)
				return (SH_ERR_DUP);
			proc->fd_backups[i] = new;
			break ;
		}
	}
	return (SH_SUCCESS);
}

/*
** NOTE: greater and lesser- and might be combinable in one function
** TODO: if fd to be closed is one of the backup fds, create another backup
*/

int			apply_and_redir(t_proc *proc, t_redir *redir)
{
	int	redirected;
	int	fd;
	int	ret;

	ret = SH_SUCCESS;
	redirected = redir_get_fd(redir);
	if ((fd = redirand_get_fd(redir)) == -1)
		return (SH_ERR_OPEN);
	if ((ret = redir_add_undo(proc, redirected)) != SH_SUCCESS)
		return (ret);
	if (ft_strequ(redir->filename, "-") &&
		(ret = redirand_check_closed(proc, redirected)) == SH_SUCCESS)
		close(redirected);
	else
	{
		close(redirected);
		if (dup2(fd, redirected) == -1)
		{
			close(fd);
			return (SH_ERR_DUP);
		}
		close(fd);
	}
	return (ret);
}

/*
** NOTE: this can be used for greater lesser and double greater
** TODO: move this in its own file
*/

int			apply_base_redir(t_proc *proc, t_redir *redir)
{
	int	redirected;
	int	fd;
	int	ret;

	redirected = redir_get_fd(redir);
	fd = redir_open_file(redir->filename, redir->token->type);
	if (fd == -1)
		return (SH_ERR_OPEN);
	if ((ret = redir_add_undo(proc, redirected)) != SH_SUCCESS)
		return (ret);
	close(redirected);
	if (dup2(fd, redirected) == -1)
	{
		close(fd);
		return (SH_ERR_DUP);
	}
	close(fd);
	return (SH_SUCCESS);
}
