/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interactive_mode.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:24:09 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/07 18:57:53 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	init_signals(t_sh *shell)
{
	struct sigaction action;

	(void)shell;
	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = ignore_signal;
	sigaction(SIGINT, &action, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	return (0);
}

int			init_interactive_mode(t_sh *shell)
{
	pid_t	pid;

	while (tcgetpgrp(SH_IN) != (pid = getpgrp()))
		kill(-pid, SIGTTIN);
	if (init_signals(shell))
		return (1);
	shell->pid = getpid();
	if (setpgid(shell->pid, shell->pid) < 0)
	{
		return (1);
	}
	tcsetpgrp(SH_IN, shell->pid);
	tcgetattr(SH_IN, &shell->old_termios);
	tcgetattr(SH_IN, &shell->current_termios);
	shell->current_termios.c_lflag &= ~(ICANON | ECHO);
	shell->current_termios.c_cc[VMIN] = 1;
	shell->current_termios.c_cc[VTIME] = 0;
	tcsetattr(SH_IN, TCSADRAIN, &shell->current_termios);
	return (0);
}
