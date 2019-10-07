/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:39:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/07 17:57:51 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	init_shell(t_sh *shell, const char **env)
{
	ft_memset(shell, 0, sizeof(shell));
	if (!(shell->env = ft_mapnew(ft_splitlen((char**)env))))
		return (1);
	copy_env(shell, env);
	return (0);
}

/*
** TODO: print errors
*/

int			main(int argc, const char **argv, const char **env)
{
	t_sh	shell;

	if (init_shell(&shell, env))
	{
		free_sh(&shell);
		return (1);
	}
	(void)argc;
	(void)argv;
	free_sh(&shell);
	// ft_printf("executed %s\n", argv[0]);
	return (0);
}
