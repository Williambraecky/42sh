/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:32:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 23:23:29 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	make_env(t_sh *shell, t_proc *proc)
{
	size_t	i;
	char	*equal;

	if (!(proc->env_backup = clone_var(shell)))
		return (SH_ERR_MALLOC);
	ft_memswap(&proc->env_backup, &shell->vars, sizeof(t_map *));
	ft_memswap(&proc->hash_backup, &shell->use_hash, sizeof(t_map *));
	i = proc->assignments.size;
	while (i--)
	{
		equal = ft_strchr(ft_vecget(&proc->assignments, i), '=');
		*equal = '\0';
		if (repl_var(shell, ft_vecget(&proc->assignments, i), equal + 1))
		{
			ft_memswap(&proc->env_backup, &shell->vars, sizeof(t_map *));
			ft_mapfilter(proc->env_backup, var_del_filter);
			ft_mapdel(proc->env_backup);
			proc->env_backup = NULL;
			return (SH_ERR_MALLOC);
		}
	}
	return (make_env_array(shell, &proc->env));
}

static void	revert_env(t_sh *shell, t_proc *proc)
{
	if (!proc->env_backup)
		return ;
	ft_memswap(&proc->env_backup, &shell->vars, sizeof(t_map *));
	ft_memswap(&proc->hash_backup, &shell->use_hash, sizeof(t_map *));
	ft_mapfilter(proc->env_backup, var_del_filter);
	ft_mapdel(proc->env_backup);
}

static int	apply_assigns(t_sh *shell, t_proc *proc)
{
	char	*current;
	char	*tmp;
	size_t	i;

	if (proc->assignments.size == 0)
		return (make_env_array(shell, &proc->env));
	if (proc->unprocessed_argv.size > 0)
		return (make_env(shell, proc));
	if (proc->parent->background)
		return (SH_SUCCESS);
	i = 0;
	while (i < proc->assignments.size)
	{
		current = (char*)ft_vecget(&proc->assignments, i);
		tmp = ft_strchr(current, '=');
		*tmp = '\0';
		if (repl_var(shell, current, tmp + 1) != SH_SUCCESS)
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
			close(proc->fd_backups[i]);
		}
	}
	return (ret);
}

/*
** NOTE: substitute all words related to arguments
** NOTE: exec command
** NOTE: redirections for backgrounded commands are done after fork
*/

int			exec_proc(t_sh *shell, t_proc *proc)
{
	int	ret;

	ret = proc_make_string(proc);
	if (ret == SH_SUCCESS)
		ret = prepare_proc(shell, proc);
	if (ret == SH_SUCCESS)
		ret = apply_assigns(shell, proc);
	if (ret == SH_SUCCESS && proc->parent->background == 0)
		ret = proc_apply_redir(proc);
	if (ret == SH_SUCCESS && proc->unprocessed_argv.size > 0 &&
		!is_builtin(shell, proc->argv[0]))
	{
		if (resolve_path(shell, proc->argv[0], &proc->path) != SH_SUCCESS)
			proc->path = NULL;
		if (proc->path && access(proc->path, X_OK) == 0 &&
			!is_dir(proc->path))
			hash_add_use_insert(shell, proc->argv[0], proc->path);
	}
	revert_env(shell, proc);
	if (ret != SH_SUCCESS)
		proc->status = ret;
	if (ret != SH_ERR_MALLOC)
		ret = proc_exec_cmd(shell, proc);
	ret = undo_redir(proc, ret);
	return (ret);
}
