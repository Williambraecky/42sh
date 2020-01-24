/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_signal_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:39:38 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/24 23:33:53 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

char	*g_sigmsg[] =
{
	[SIGABRT] = "abort",
	[SIGALRM] = "alarm",
	[SIGBUS] = "bus error",
	[SIGCHLD] = "death of child",
	[SIGCONT] = "continued",
	[SIGEMT] = "EMT instruction",
	[SIGFPE] = "floating point exception",
	[SIGHUP] = "hangup",
	[SIGILL] = "illegal hardware instruction",
	[SIGINFO] = "status request from keyboard",
	[SIGINT] = "interrupt",
	[SIGIO] = "i/o ready",
	[SIGKILL] = "killed",
	[SIGPIPE] = "broken pipe",
	[SIGPROF] = "profile signal",
	[SIGQUIT] = "quit",
	[SIGSEGV] = "segmentation fault",
	[SIGTERM] = "terminated",
	[SIGTRAP] = "trace trap",
	[SIGURG] = "urgent condition",
	[SIGUSR1] = "user-defined signal 1",
	[SIGUSR2] = "user-defined signal 2",
	[SIGVTALRM] = "virtual time alarm",
	[SIGWINCH] = "window size changed",
	[SIGXCPU] = "cpu limit exceeded",
	[SIGXFSZ] = "file size limit exceeded",
	[SIGSTOP] = "suspended (signal)",
	[SIGTSTP] = "suspended",
	[SIGTTIN] = "suspended (tty input)",
	[SIGTTOU] = "suspended (tty output)",
	[50] = NULL,
};

/*
** NOTE: status is the return from wait
*/

char	*get_signal_str(t_proc *proc)
{
	if (proc->status_str)
		return (proc->status_str);
	if (!proc->stopped && !proc->completed)
		proc->status_str = ft_strdup("running");
	else if (WIFCONTINUED(proc->status))
		proc->status_str = ft_strdup(g_sigmsg[SIGCONT]);
	else if (WIFSTOPPED(proc->status) && g_sigmsg[WSTOPSIG(proc->status)])
		proc->status_str = ft_strdup(g_sigmsg[WSTOPSIG(proc->status)]);
	else if (WIFSIGNALED(proc->status) && g_sigmsg[WTERMSIG(proc->status)])
		proc->status_str = ft_strdup(g_sigmsg[WTERMSIG(proc->status)]);
	else if (WIFEXITED(proc->status))
	{
		if (WEXITSTATUS(proc->status) == 0)
			proc->status_str = ft_strdup("done");
		else
			proc->status_str = ft_strformat("exit %d",
				WEXITSTATUS(proc->status));
	}
	return (proc->status_str);
}
