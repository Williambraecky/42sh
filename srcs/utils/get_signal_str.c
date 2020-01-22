/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_signal_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:39:38 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/22 21:35:36 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"


	// if (signam == "ABRT")   { msg[signum] = "abort" }
	// if (signam == "ALRM")   { msg[signum] = "alarm" }
	// if (signam == "BUS")    { msg[signum] = "bus error" }
	// if (signam == "CHLD")   { msg[signum] = "death of child" }
	// if (signam == "CLD")    { msg[signum] = "death of child" }
	// if (signam == "CONT")   { msg[signum] = "continued" }
	// if (signam == "EMT")    { msg[signum] = "EMT instruction" }
	// if (signam == "FPE")    { msg[signum] = "floating point exception" }
	// if (signam == "HUP")    { msg[signum] = "hangup" }
	// if (signam == "ILL")    { msg[signum] = "illegal hardware instruction" }
	// if (signam == "INFO")   { msg[signum] = "status request from keyboard" }
	// if (signam == "INT")    { msg[signum] = "interrupt" }
	// if (signam == "IO")     { msg[signum] = "i/o ready" }
	// if (signam == "IOT")    { msg[signum] = "IOT instruction" }
	// if (signam == "KILL")   { msg[signum] = "killed" }
	// if (signam == "LOST")	{ msg[signum] = "resource lost" }
	// if (signam == "PIPE")   { msg[signum] = "broken pipe" }
	// if (signam == "POLL")	{ msg[signum] = "pollable event occurred" }
	// if (signam == "PROF")   { msg[signum] = "profile signal" }
	// if (signam == "PWR")    { msg[signum] = "power fail" }
	// if (signam == "QUIT")   { msg[signum] = "quit" }
	// if (signam == "SEGV")   { msg[signum] = "segmentation fault" }
	// if (signam == "SYS")    { msg[signum] = "invalid system call" }
	// if (signam == "TERM")   { msg[signum] = "terminated" }
	// if (signam == "TRAP")   { msg[signum] = "trace trap" }
	// if (signam == "URG")	{ msg[signum] = "urgent condition" }
	// if (signam == "USR1")   { msg[signum] = "user-defined signal 1" }
	// if (signam == "USR2")   { msg[signum] = "user-defined signal 2" }
	// if (signam == "VTALRM") { msg[signum] = "virtual time alarm" }
	// if (signam == "WINCH")  { msg[signum] = "window size changed" }
	// if (signam == "XCPU")   { msg[signum] = "cpu limit exceeded" }
	// if (signam == "XFSZ")   { msg[signum] = "file size limit exceeded" }

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
