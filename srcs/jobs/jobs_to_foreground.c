/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_to_foreground.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 00:38:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 01:05:16 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** NOTE: this is unnecessary for jobs that only contain a builtin
** NOTE: procedure to put a cmd to foreground
** NOTE: wake flag is if the process previously was asleep (due to ctrl+z)
*/

int		jobs_to_foreground(t_sh *shell, t_cmd *cmd, int wake)
{
	if (cmd->pgid == 0)
		return (SH_SUCCESS);
	tcsetpgrp(STDIN_FILENO, cmd->pgid);
	if (wake)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &cmd->termios);
		if (kill(-cmd->pgid, SIGCONT) < 0)
			return (SH_ERR_KILL);
	}
	job_wait(cmd);
	tcsetpgrp(STDIN_FILENO, shell->pid);
	tcgetattr(STDIN_FILENO, &cmd->termios);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &shell->current_termios);
	return (SH_SUCCESS);
}
