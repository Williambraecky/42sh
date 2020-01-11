/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:32:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/11 15:22:04 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	make_new_env(t_sh *shell, t_proc *proc)
{
	char	*current;
	char	*tmp;
	size_t	i;

	if (proc->assignments.size == 0)
		return (SH_SUCCESS);
	if ((proc->env_backup = ft_mapclone(shell->env)))
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

/*
** NOTE: compute redirections
** NOTE: substitute all words related to arguments
** NOTE: exec command
*/

int			exec_proc(t_sh *shell, t_proc *proc)
{
	int	ret;

	ret = SH_SUCCESS;
	if (ret == SH_SUCCESS)
		ret = apply_assigns(shell, proc);
	if (ret == SH_SUCCESS)
		ret = proc_apply_redir(shell, proc);
	if (ret == SH_SUCCESS)
		;//exec command
	if (proc->env_backup)
	{
		ft_memswap(&proc->env_backup, &shell->env, sizeof(t_map *));
		ft_mapfilter(proc->env_backup, map_del_filter);
		ft_mapdel(proc->env_backup);
	}
	return (ret);
}
