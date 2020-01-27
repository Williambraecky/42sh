/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:51:10 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 23:15:33 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			apply_dlesser_redir(t_proc *proc, t_redir *redir)
{
	int	redirected;
	int	fd;
	int	ret;

	redirected = redir_get_from(redir);
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
	return (redir->to);
}

static int	redirand_check_closed(t_proc *proc, int fd)
{
	size_t	i;
	int		new;

	if (proc->parent->background)
		return (SH_SUCCESS);
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
*/

int			apply_and_redir(t_proc *proc, t_redir *redir)
{
	int	redirected;
	int	fd;
	int	ret;

	redirected = redir_get_from(redir);
	if (redir_open_file(redir) != SH_SUCCESS)
		return (SH_ERR_OPEN);
	fd = redirand_get_fd(redir);
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
		if (!(ft_strisnumber(redir->filename) && ft_atoi(redir->filename) >= 0))
			close(fd);
	}
	return (ret);
}

/*
** NOTE: this can be used for greater lesser and double greater
*/

int			apply_base_redir(t_proc *proc, t_redir *redir)
{
	int	redirected;
	int	fd;
	int	ret;

	redirected = redir_get_from(redir);
	if (redir_open_file(redir))
		return (SH_ERR_OPEN);
	fd = redir->to;
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
