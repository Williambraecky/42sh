/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_to_foreground.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 00:38:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/05 14:42:26 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
	if (shell->interactive_mode)
		tcsetpgrp(STDIN_FILENO, cmd->pgid);
	if (wake)
	{
		if (shell->interactive_mode)
			tcsetattr(STDIN_FILENO, TCSADRAIN, &cmd->termios);
		if (kill(-cmd->pgid, SIGCONT) < 0)
			return (SH_ERR_KILL);
	}
	job_wait(shell, cmd);
	if (shell->interactive_mode)
		tcsetpgrp(STDIN_FILENO, shell->pid);
	if (job_contains(shell, cmd) && shell->interactive_mode)
		tcgetattr(STDIN_FILENO, &cmd->termios);
	if (shell->interactive_mode)
		tcsetattr(STDIN_FILENO, TCSADRAIN, &shell->old_termios);
	return (SH_SUCCESS);
}
