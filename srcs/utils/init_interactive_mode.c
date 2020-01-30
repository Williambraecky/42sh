/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interactive_mode.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:24:09 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/30 22:59:22 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	init_signals(t_sh *shell)
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
}

int			init_interactive_mode(t_sh *shell)
{
	pid_t	pid;
	char	*term_env;

	shell->job_control = 1;
	tcgetattr(SH_IN, &shell->old_termios);
	if (get_var(shell, "TERM", &term_env))
		return (1);
	tgetent(NULL, term_env);
	while (tcgetpgrp(SH_IN) != (pid = getpgrp()))
		kill(-pid, SIGTTIN);
	init_signals(shell);
	if (setpgid(shell->pid, shell->pid) < 0)
		return (1);
	tcsetpgrp(SH_IN, shell->pid);
	tcgetattr(SH_IN, &shell->current_termios);
	shell->current_termios.c_lflag &= ~(ICANON | ECHO);
	shell->current_termios.c_cc[VMIN] = 1;
	shell->current_termios.c_cc[VTIME] = 0;
	return (0);
}
