/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:59:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 16:58:58 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** TODO: define behaviour when jobs are running in background
*/

int		exit_builtin(int argc, char **argv, t_sh *shell)
{
	int	ret;

	ret = 0;
	if (argc > 1)
		ret = ft_atoi(argv[1]);
	if (getpid() == shell->pid)
		shell->running = 0;
	return (ret);
}
