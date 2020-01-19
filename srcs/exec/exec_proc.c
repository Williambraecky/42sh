/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:32:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/19 04:07:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** TODO: we don't free proc->env here if the function fails
*/

static int	make_env(t_sh *shell, t_proc *proc)
{
	size_t	i;
	size_t	j;

	if (!(proc->env = ft_memalloc(sizeof(char*) *
		(shell->env->size + proc->assignments.size + 1))))
		return (SH_ERR_MALLOC);
	if (make_env_array_no_malloc(shell, proc->env) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	i = 0;
	while (proc->env[i])
		i++;
	j = 0;
	while (j < proc->assignments.size)
	{
		if (!(proc->env[i++] =
			ft_strdup((char*)ft_vecget(&proc->assignments, j))))
			return (SH_ERR_MALLOC);
		j++;
	}
	return (SH_SUCCESS);
}

static int	apply_assigns(t_sh *shell, t_proc *proc)
{
	char	*current;
	char	*tmp;
	size_t	i;

	if (proc->unprocessed_argv.size > 0)
		return (make_env(shell, proc));
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
			close(proc->fd_backups[i]);
		}
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

	ret = proc_make_string(proc);
	if (ret == SH_SUCCESS)
		ret = prepare_proc(shell, proc);
	if (ret == SH_SUCCESS)
		ret = apply_assigns(shell, proc);
	if (ret == SH_SUCCESS)
		ret = proc_apply_redir(shell, proc);
	if (ret != SH_SUCCESS)
		proc->status = ret;
	ret = proc_exec_cmd(shell, proc);
	ret = undo_redir(proc, ret);
	return (ret);
}
