/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_apply_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:10:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/10 19:19:13 by wbraeckm         ###   ########.fr       */
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

/*
** TODO: open files for redirections and add the
**    fd to the good io number in proc->io
*/

static int	actual_redir(t_sh *shell, t_proc *proc,
	t_redir *redir, char *real_filename)
{
	(void)shell;
	(void)proc;
	(void)redir;
	(void)real_filename;
	return (SH_SUCCESS);
}

int			proc_apply_redir(t_sh *shell, t_proc *proc)
{
	t_redir	*redir;
	char	*sub_filename;
	size_t	i;
	int		ret;

	i = 0;
	while (i < proc->redirections.size)
	{
		redir = (t_redir*)ft_vecget(&proc->redirections, i++);
		if (proxy_substitute(shell, redir->filename, &sub_filename))
			return (SH_ERR_MALLOC);
		if ((ret = actual_redir(shell, proc,
			redir, sub_filename)) != SH_SUCCESS)
			return (ret);
	}
	return (SH_SUCCESS);
}
