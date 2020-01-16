/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_proc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 01:36:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/16 02:32:34 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


// if (make_env_array(shell, &proc->env) != SH_SUCCESS)
// {
// 	ft_freesplit(proc->argv);
// 	proc->argv = NULL;
// 	return (SH_ERR_MALLOC);
// }

static int	prepare_args(t_sh *shell, t_proc *proc)
{
	size_t	i;
	char	*curr;

	if (proc->unprocessed_argv.size == 0)
		return (SH_SUCCESS);
	if (!(proc->argv =
		ft_memalloc(sizeof(*(proc->argv)) * (proc->unprocessed_argv.size + 1))))
		return (SH_ERR_MALLOC);
	i = 0;
	while (i < proc->unprocessed_argv.size)
	{
		curr = (char*)ft_vecget(&proc->unprocessed_argv, i);
		if (proxy_substitute(shell, curr, &(proc->argv[i])) != SH_SUCCESS)
		{
			ft_freesplit(proc->argv);
			proc->argv = NULL;
			return (SH_ERR_MALLOC);
		}
		i++;
	}
	return (SH_SUCCESS);
}

static int	prepare_assigns(t_sh *shell, t_proc *proc)
{
	size_t	i;
	char	*tmp;
	char	*new;

	i = 0;
	while (i < proc->assignments.size)
	{
		tmp = (char*)ft_vecget(&proc->assignments, i);
		if (proxy_substitute(shell, tmp, &new) != SH_SUCCESS)
			return (SH_ERR_MALLOC);
		free(tmp);
		ft_vecset(&proc->assignments, new, i);
		i++;
	}
	return (SH_SUCCESS);
}

static int	prepare_redirections(t_sh *shell, t_proc *proc)
{
	size_t	i;
	t_redir	*redir;
	char	*tmp;

	i = 0;
	while (i < proc->redirections.size)
	{
		redir = (t_redir*)ft_vecget(&proc->redirections, i);
		tmp = redir->filename;
		if (proxy_substitute(shell, tmp, &redir->filename) != SH_SUCCESS)
			return (SH_ERR_MALLOC);
		free(tmp);
		i++;
	}
	return (SH_SUCCESS);
}

int		prepare_proc(t_sh *shell, t_proc *proc)
{
	int	ret;

	ret = prepare_args(shell, proc);
	if (ret == SH_SUCCESS)
		ret = prepare_assigns(shell, proc);
	if (ret == SH_SUCCESS)
		ret = prepare_redirections(shell, proc);
	return (ret);
}
