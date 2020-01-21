/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:59:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 22:03:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"

/*
** TODO: define behaviour when jobs are stopped
** TODO: better handle arg reading
*/

static int	check_stopped_jobs(t_sh *shell)
{
	size_t	size;
	t_cmd	*cmd;

	size = shell->jobs.size;
	while (size--)
	{
		cmd = ft_vecget(&shell->jobs, size);
		if (job_is_stopped(cmd))
			return (1);
	}
	return (0);
}

static void	kill_jobs(t_sh *shell)
{
	size_t	size;
	t_cmd	*cmd;

	size = shell->jobs.size;
	while (size--)
	{
		cmd = ft_vecget(&shell->jobs, size);
		if (job_is_stopped(cmd))
		{
			kill(-cmd->pgid, SIGKILL);
		}
	}
}

int			exit_builtin(int argc, char **argv, t_sh *shell)
{
	int	ret;

	ret = 0;
	if (argc > 1)
		ret = ft_atoi(argv[1]);
	ret = (ret % 256 + 256) % 256;
	if (getpid() != shell->pid)
		return (ret);
	if (check_stopped_jobs(shell))
	{
		if (ft_strstartswith((char*)ft_vecgettop(&shell->history), "exit"))
			kill_jobs(shell);//TODO: kill jobs
		else
		{
			ft_dprintf(2, "42sh: exit: there are stopped jobs.\n");
			return (1);
		}
	}
	shell->running = 0;
	shell->stop_code = ret;
	return (shell->stop_code);
}
