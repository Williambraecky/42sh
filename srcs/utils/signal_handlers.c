/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:29:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/16 16:41:45 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

sig_atomic_t	g_winchange = 0;

void	window_change_signal(int signo)
{
	(void)signo;
	g_winchange = 1;
}

void	ignore_signal(int signo)
{
	(void)signo;
}
