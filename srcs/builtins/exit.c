/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:59:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/18 17:59:16 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** TODO: define behaviour when jobs are stopped
** TODO: better handle arg reading
*/

int		exit_builtin(int argc, char **argv, t_sh *shell)
{
	int	ret;

	ret = 0;
	if (argc > 1)
		ret = ft_atoi(argv[1]);
	if (shell->jobs.size != 0)
	{
		ft_dprintf(2, "42sh: exit: there are stopped jobs.\n");
		return (1);
	}
	if (getpid() == shell->pid)
		shell->running = 0;
	shell->stop_code = (ret % 256 + 256) % 256;
	return (0);
}
