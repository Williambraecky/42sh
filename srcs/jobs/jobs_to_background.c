/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_to_background.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 00:44:18 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 17:26:55 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		jobs_to_background(t_sh *shell, t_cmd *cmd, int wake)
{
	if (wake)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &cmd->termios);
		if (kill(-cmd->pgid, SIGCONT) < 0)
			return (SH_ERR_KILL);
	}
	else
		jobs_add(shell, cmd, 1);
	return (SH_SUCCESS);
}
