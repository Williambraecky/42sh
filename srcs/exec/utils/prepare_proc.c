/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_proc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 01:36:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 23:02:45 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	prepare_args(t_sh *shell, t_proc *proc)
{
	size_t	i;
	char	*curr;
	int		ret;

	if (proc->unprocessed_argv.size == 0)
		return (SH_SUCCESS);
	if (!(proc->argv =
		ft_memalloc(sizeof(*(proc->argv)) * (proc->unprocessed_argv.size + 1))))
		return (SH_ERR_MALLOC);
	i = 0;
	while (i < proc->unprocessed_argv.size)
	{
		curr = (char*)ft_vecget(&proc->unprocessed_argv, i);
		if ((ret = substitute(shell, curr, &(proc->argv[i]), ~SUB_ASSIGN))
			!= SH_SUCCESS)
			return (ret);
		i++;
	}
	return (SH_SUCCESS);
}

static int	assign_substitute(t_sh *shell, char *assign, char **result)
{
	char	*equals;
	char	*sub;
	int		ret;

	equals = ft_strchr(assign, '=');
	if ((ret = substitute(shell, equals + 1, &sub, ~0)) != SH_SUCCESS)
		return (ret);
	equals[1] = '\0';
	if (!(*result = ft_strjoin(assign, sub)))
	{
		free(sub);
		return (SH_ERR_MALLOC);
	}
	free(sub);
	return (SH_SUCCESS);
}

static int	prepare_assigns(t_sh *shell, t_proc *proc)
{
	size_t	i;
	char	*tmp;
	char	*new;
	int		ret;

	i = 0;
	while (i < proc->assignments.size)
	{
		tmp = (char*)ft_vecget(&proc->assignments, i);
		if ((ret = assign_substitute(shell, tmp, &new)) != SH_SUCCESS)
			return (ret);
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
	int		ret;

	i = 0;
	while (i < proc->redirections.size)
	{
		redir = (t_redir*)ft_vecget(&proc->redirections, i);
		tmp = redir->filename;
		if (redir->token->type == T_DOUBLE_LESSER)
			tmp = NULL;
		else if ((ret = substitute(shell, tmp, &redir->filename, ~SUB_ASSIGN))
			!= SH_SUCCESS)
			return (ret);
		if (redir->token->type == T_DOUBLE_LESSER &&
			(ret = prepare_hdoc(shell, (t_hdoc*)redir->token)) != SH_SUCCESS)
			return (ret);
		free(tmp);
		i++;
	}
	return (SH_SUCCESS);
}

int			prepare_proc(t_sh *shell, t_proc *proc)
{
	int	ret;

	ret = prepare_args(shell, proc);
	if (ret == SH_SUCCESS)
		ret = prepare_assigns(shell, proc);
	if (ret == SH_SUCCESS)
		ret = prepare_redirections(shell, proc);
	return (ret);
}
