/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:59:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 23:03:17 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"

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

static int	handle_args(int argc, char **argv, int *ret)
{
	if (!ft_strisnumber(argv[1]))
		ft_dprintf(2, "42sh: exit: %s: numerical arguemnt expected\n", argv[1]);
	else if (argc > 2)
	{
		ft_dprintf(2, "42sh: exit: too many arguments\n");
		return (1);
	}
	else
		*ret = ft_atoi(argv[1]);
	return (0);
}

int			exit_builtin(int argc, char **argv, t_sh *shell)
{
	int	ret;

	ret = 0;
	if (argc > 1 && handle_args(argc, argv, &ret))
		return (1);
	ret = (ret % 256 + 256) % 256;
	if (getpid() != shell->pid)
		return (ret);
	if (check_stopped_jobs(shell))
	{
		if (ft_strstartswith((char*)ft_vecgettop(&shell->history), "exit"))
			kill_jobs(shell);
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
