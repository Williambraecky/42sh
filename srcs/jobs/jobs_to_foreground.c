/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_to_foreground.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 00:38:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/20 22:30:56 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** NOTE: this is unnecessary for jobs that only contain a builtin
** NOTE: procedure to put a cmd to foreground
** NOTE: wake flag is if the process previously was asleep (due to ctrl+z)
*/

static int	job_contains(t_sh *shell, t_cmd *cmd)
{
	size_t	i;

	i = shell->jobs.size;
	while (i--)
		if (ft_vecget(&shell->jobs, i) == (void*)cmd)
			return (1);
	return (0);
}

int			jobs_to_foreground(t_sh *shell, t_cmd *cmd, int wake)
{
	tcsetpgrp(STDIN_FILENO, cmd->pgid);
	if (wake)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &cmd->termios);
		if (kill(-cmd->pgid, SIGCONT) < 0)
			return (SH_ERR_KILL);
	}
	job_wait(shell, cmd);
	tcsetpgrp(STDIN_FILENO, shell->pid);
	if (job_contains(shell, cmd))
		tcgetattr(STDIN_FILENO, &cmd->termios);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &shell->current_termios);
	return (SH_SUCCESS);
}
