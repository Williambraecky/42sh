/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interactive_mode.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:24:09 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 17:02:18 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** TODO: most of this should be done in the prompt code
*/

static int	init_signals(t_sh *shell)
{
	struct sigaction action;

	(void)shell;
	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = ignore_signal;
	sigaction(SIGINT, &action, NULL);
	signal(SIGWINCH, window_change_signal);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	return (0);
}

/*
** TODO: most of this should be done in the prompt code
*/

int			init_interactive_mode(t_sh *shell)
{
	pid_t	pid;
	char	*term_env;

	tcgetattr(SH_IN, &shell->old_termios);
	if (get_env(shell, "TERM", &term_env))
		return (1);
	tgetent(NULL, term_env);
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
	tcgetattr(SH_IN, &shell->current_termios);
	shell->current_termios.c_lflag &= ~(ICANON | ECHO);
	shell->current_termios.c_cc[VMIN] = 1;
	shell->current_termios.c_cc[VTIME] = 0;
	return (0);
}
