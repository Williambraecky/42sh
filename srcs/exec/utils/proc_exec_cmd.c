/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_exec_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 23:57:32 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 01:24:05 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

static void	close_backup_fds_fork(t_proc *proc)
{
	size_t	i;

	i = PROC_FD_BACKUP_SIZE;
	while (i--)
		close(proc->fd_backups[i]);
}

static int	exec_builtin(t_sh *shell, t_proc *proc)
{
	t_bltin	*bltin;
	int		ret;

	bltin = ft_mapget(shell->builtins, proc->argv[0]);
	ret = bltin->fnc_ptr((int)proc->unprocessed_argv.size, proc->argv, shell);
	if (proc->pid)
		exit(ret);
	return (ret);
}

static void	exec_bin(t_sh *shell, t_proc *proc)
{
	char	*path;

	if (resolve_path(shell, proc->argv[0], &path) != SH_SUCCESS)
	{
		ft_dprintf(2, "42sh: command not found: %s\n", proc->argv[0]);
		exit(127);
	}
	execve(path, proc->argv, proc->env);
	ft_dprintf(2, "42sh: error executing: %s\n", proc->argv[0]);
	exit(127);
}

/*
** NOTE: prepare command ie create argv and env for exec
** NOTE: fetch exec type
** NOTE: fork if necessary, if forked we can close all backup_fds
** NOTE: exec properly
** TODO: reduce lines
*/

int			proc_exec_cmd(t_sh *shell, t_proc *proc)
{
	int		ret;
	int		builtin;
	int		need_fork;
	pid_t	pid;

	ret = prepare_args(shell, proc);
	builtin = is_builtin(shell, proc->argv[0]);
	need_fork = !builtin || proc->next != NULL;
	pid = 0;
	if (!need_fork || (pid = fork()) == 0)
	{
		if (need_fork)
			close_backup_fds_fork(proc);
		if (builtin)
			ret = exec_builtin(shell, proc);
		else
			exec_bin(shell, proc);
	}
	else if (pid == -1)
		ret = SH_ERR_FORK;
	else
	{
		proc->pid = pid;
		if (proc->parent->pgid == 0)
			proc->parent->pgid = pid;
		setpgid(pid, proc->parent->pgid);
	}
	ft_freesplit(proc->argv);
	ft_freesplit(proc->env);
	return (ret);
}
