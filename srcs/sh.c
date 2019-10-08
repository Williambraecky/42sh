/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:39:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/08 17:26:27 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "prompt.h"

/*
** TODO: Make sure variables such as HOME PWD are not validated using env vars
*/

static int	init_shell(t_sh *shell, const char **env)
{
	ft_memset(shell, 0, sizeof(shell));
	if (!(shell->env = ft_mapnew(100)))
		return (1);
	copy_env(shell, env);
	if ((shell->prompt_mode = isatty(SH_IN)))
		if (init_interactive_mode(shell))
			return (1);
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
	ft_printf("Mode %d", shell.prompt_mode);
	handle_prompt(&shell);
	free_sh(&shell);
	// ft_printf("executed %s\n", argv[0]);
	return (0);
}
