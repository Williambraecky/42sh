/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_apply_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:10:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/11 17:26:15 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
** TODO: use real substitute function
*/

static int	proxy_substitute(t_sh *shell, char *str, char **result)
{
	(void)shell;
	if (!(*result = ft_strdup(str)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

static int	actual_redir(t_proc *proc, t_redir *redir)
{
	if (redir->token->type == T_GREATER ||
		redir->token->type == T_DOUBLE_GREATER ||
		redir->token->type == T_LESSER)
		return (apply_base_redir(proc, redir));
	else if (redir->token->type == T_LESSER_AND ||
		redir->token->type == T_GREATER_AND)
		return (apply_and_redir(proc, redir));
	else if (redir->token->type == T_DOUBLE_LESSER)
		return (apply_dlesser_redir(proc, redir));
	return (SH_SUCCESS);
}

static int	redir_apply_pipe(t_proc *proc, int io, int to)
{
	int	ret;

	if (io)
	{
		io = proc->io.out;
		if ((ret = redir_add_undo(proc, to)) != SH_SUCCESS)
			return (ret);
		close(to);
		if (dup2(io, to) == -1)
		{
			close(io);
			return (SH_ERR_DUP);
		}
		close(io);
	}
	return (SH_SUCCESS);
}

int			proc_apply_redir(t_sh *shell, t_proc *proc)
{
	t_redir	*redir;
	size_t	i;
	int		ret;

	i = 0;
	if ((ret = redir_apply_pipe(proc, proc->io.out, 1)) != SH_SUCCESS)
		return (ret);
	if ((ret = redir_apply_pipe(proc, proc->io.in, 0)) != SH_SUCCESS)
		return (ret);
	while (i < proc->redirections.size)
	{
		redir = (t_redir*)ft_vecget(&proc->redirections, i++);
		if (proxy_substitute(shell, redir->filename, &redir->filename))
			return (SH_ERR_MALLOC);
		if ((ret = actual_redir(proc, redir)) != SH_SUCCESS)
			return (ret);
	}
	return (SH_SUCCESS);
}