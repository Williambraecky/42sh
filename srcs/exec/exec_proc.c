/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:32:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 14:28:36 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	prepare_args(t_sh *shell, t_proc *proc)
{
	size_t	i;
	char	*curr;

	if (!(proc->argv =
		ft_memalloc(sizeof(*(proc->argv)) * (proc->unprocessed_argv.size + 1))))
		return (SH_ERR_MALLOC);
	i = 0;
	while (i < proc->unprocessed_argv.size)
	{
		curr = ((t_token*)ft_vecget(&proc->unprocessed_argv, i))->str;
		if (proxy_substitute(shell, curr, &(proc->argv[i])) != SH_SUCCESS)
		{
			ft_freesplit(proc->argv);
			proc->argv = NULL;
			return (SH_ERR_MALLOC);
		}
		i++;
	}
	if (make_env_array(shell, &proc->env) != SH_SUCCESS)
	{
		ft_freesplit(proc->argv);
		proc->argv = NULL;
		return (SH_ERR_MALLOC);
	}
	return (SH_SUCCESS);
}

/*
** TODO: those assigns need to be substituted aswell
*/

static int	make_new_env(t_sh *shell, t_proc *proc)
{
	char	*current;
	char	*tmp;
	size_t	i;

	if (proc->assignments.size == 0)
		return (SH_SUCCESS);
	if (!(proc->env_backup = ft_mapclone(shell->env)))
		return (SH_ERR_MALLOC);
	i = 0;
	ft_memswap(&proc->env_backup, &shell->env, sizeof(t_map *));
	while (i < proc->assignments.size)
	{
		current = (char*)ft_vecget(&proc->assignments, i++);
		tmp = ft_strchr(current, '=');
		*tmp = '\0';
		if (repl_env(shell, current, tmp + 1) != SH_SUCCESS)
		{
			ft_memswap(&proc->env_backup, &shell->env, sizeof(t_map *));
			ft_mapfilter(proc->env_backup, map_del_filter);
			ft_mapdel(proc->env_backup);
			return (SH_ERR_MALLOC);
		}
		*tmp = '=';
	}
	return (SH_SUCCESS);
}

static int	apply_assigns(t_sh *shell, t_proc *proc)
{
	char	*current;
	char	*tmp;
	size_t	i;

	if (proc->unprocessed_argv.size > 0)
		return (make_new_env(shell, proc));
	i = 0;
	while (i < proc->assignments.size)
	{
		current = (char*)ft_vecget(&proc->assignments, i);
		tmp = ft_strchr(current, '=');
		*tmp = '\0';
		if (repl_internal(shell, current, tmp + 1) != SH_SUCCESS)
			return (SH_ERR_MALLOC);
		*tmp = '=';
		i++;
	}
	return (SH_SUCCESS);
}

static int	undo_redir(t_proc *proc, int ret)
{
	size_t	i;

	i = PROC_FD_BACKUP_SIZE;
	while (i--)
	{
		if (proc->fd_backups[i] != -1)
		{
			close(i);
			if (dup2(proc->fd_backups[i], i) == -1)
				ret = SH_ERR_DUP;
		}
		close(proc->fd_backups[i]);
	}
	return (ret);
}

/*
** NOTE: substitute all words related to arguments
** NOTE: exec command
*/

int			exec_proc(t_sh *shell, t_proc *proc)
{
	int	ret;

	ret = SH_SUCCESS;
	if (ret == SH_SUCCESS)
		ret = apply_assigns(shell, proc);
	if (ret == SH_SUCCESS && proc->unprocessed_argv.size > 0)
		ret = prepare_args(shell, proc);
	if (ret == SH_SUCCESS)
		ret = proc_apply_redir(shell, proc);
	if (ret == SH_SUCCESS)
		ret = proc_exec_cmd(shell, proc);
	ret = undo_redir(proc, ret);
	if (proc->env_backup && proc->env_backup->nodes)
	{
		ft_memswap(&proc->env_backup, &shell->env, sizeof(t_map *));
		ft_mapfilter(proc->env_backup, map_del_filter);
		ft_mapdel(proc->env_backup);
	}
	return (ret);
}
