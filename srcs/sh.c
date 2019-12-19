/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:39:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/19 14:31:18 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "prompt.h"

/*
** TODO: Variables such as HOME avec PWD should not be gotten from env vars
**   since they can be changed by the user
*/

static int	init_shell(t_sh *shell, const char **env)
{
	ft_memset(shell, 0, sizeof(shell));
	if (!(shell->internals = ft_mapnew(100)))
		return (1);
	if (!(shell->env = ft_mapnew(100)))
		return (1);
	if (!(shell->aliases = ft_mapnew(10)))
		return (1);
	if (!(shell->builtins = ft_mapnew(30)))
		return (1);
	if (!(shell->use_hash = ft_mapnew(30)))
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
	char	*line;

	if (init_shell(&shell, env))
	{
		free_sh(&shell);
		return (1);
	}
	(void)argc;
	(void)argv;
	handle_prompt(&shell, &line);
	ft_printf("\nLine: ");
	ft_putnonprint(line);
	ft_putchar('\n');
	free(line);
	free_sh(&shell);
	// ft_printf("executed %s\n", argv[0]);
	return (0);
}
