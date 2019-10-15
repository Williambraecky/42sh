/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:49:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/15 16:19:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: Main shell free procedure add fields to be freed here
*/

void	free_sh(t_sh *shell)
{
	struct sigaction action;

	ft_mapdel(shell->env);
	if (shell->prompt_mode)
	{
		tcsetattr(SH_IN, TCSADRAIN, &shell->old_termios);
		ft_memset(&action, 0, sizeof(action));
		action.sa_handler = SIG_DFL;
		sigaction(SIGINT, &action, NULL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
	}
}
