/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:59:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/16 00:18:10 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** TODO: define behaviour when jobs are running in background
** TODO: better handle arg reading
*/

int		exit_builtin(int argc, char **argv, t_sh *shell)
{
	int	ret;

	ret = 0;
	if (argc > 1)
		ret = ft_atoi(argv[1]);
	if (getpid() == shell->pid)
		shell->running = 0;
	shell->stop_code = ret;
	return (0);
}
