/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_exec_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 23:57:32 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/30 23:20:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	fork_reset_stuff(t_sh *shell, t_proc *proc)
{
	size_t	i;
	int		ret;

	i = PROC_FD_BACKUP_SIZE;
	while (i--)
		if (proc->fd_backups[i] != -1)
			close(proc->fd_backups[i]);
	if (shell->interactive_mode)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGWINCH, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!proc->block_sigtstp)
			signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
	}
	if (proc->io.pipe_close)
		close(proc->io.pipe_close);
	if (proc->parent->background && (ret = proc_apply_redir(proc)))
		proc->status = ret;
}

static int	exec_builtin(t_sh *shell, t_proc *proc, int bg)
{
	t_bltin	*bltin;
	int		ret;

	ft_reset_opt();
	if (proc->status != 0 && bg)
		exit(1);
	if (proc->status == 0)
	{
		bltin = ft_mapget(shell->builtins, proc->argv[0]);
		ret = bltin->fnc_ptr((int)proc->unprocessed_argv.size,
			proc->argv, shell);
	}
	if (bg)
		exit(ret);
	proc->status = ret;
	proc->completed = 1;
	proc->stopped = 1;
	return (ret);
}

static void	exec_bin(t_proc *proc)
{
	if (proc->status != 0)
		exit(1);
	if (!proc->argv)
		exit(0);
	if (!proc->path)
	{
		ft_dprintf(2, "42sh: command not found: %s\n", proc->argv[0]);
		exit(127);
	}
	if (access(proc->path, X_OK) == -1)
	{
		ft_dprintf(2, "42sh: permission denied: %s\n", proc->argv[0]);
		exit(127);
	}
	if (is_dir(proc->path))
	{
		ft_dprintf(2, "42sh: is a directory: %s\n", proc->argv[0]);
		exit(127);
	}
	execve(proc->path, proc->argv, proc->env);
	ft_dprintf(2, "42sh: error executing: %s\n", proc->argv[0]);
	exit(127);
}

static int	post_fork(t_sh *shell, t_proc *proc, int builtin, int need_fork)
{
	int		ret;

	ret = SH_SUCCESS;
	if (need_fork)
		fork_reset_stuff(shell, proc);
	if (builtin)
		ret = exec_builtin(shell, proc, need_fork);
	else
		exec_bin(proc);
	return (ret);
}

/*
** NOTE: prepare command ie create argv and env for exec
** NOTE: fetch exec type
** NOTE: fork if necessary, if forked we can close all backup_fds
** NOTE: exec properly
*/

int			proc_exec_cmd(t_sh *shell, t_proc *proc)
{
	int		ret;
	int		builtin;
	int		need_fork;
	pid_t	pid;

	ret = SH_SUCCESS;
	builtin = proc->argv && proc->argv[0] && is_builtin(shell, proc->argv[0]);
	need_fork = !builtin || proc->next != NULL || proc->parent->background;
	pid = 0;
	if (!need_fork || (pid = fork()) == 0)
		ret = post_fork(shell, proc, builtin, need_fork);
	else if (pid == -1)
		ret = SH_ERR_FORK;
	else
	{
		proc->pid = pid;
		if (proc->parent->pgid == 0)
			proc->parent->pgid = pid;
		setpgid(pid, proc->parent->pgid);
	}
	return (ret);
}
