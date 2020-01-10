/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:39:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/10 15:21:31 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "prompt.h"

/*
** TODO: Variables such as HOME avec PWD should not be gotten from env vars
**   since they can be changed by the user
*/
char		*g_error_str[] =
{
	[SH_ERR_NOEXIST] = "no exist error",
	[SH_ERR_MALLOC] = "malloc error",
	[SH_ERR_ENV_NOEXIST] = "env does not exist",
	[SH_ERR_OPEN_HIST] = "open history fail",
	[SH_ERR_OPEN_DIR] = "open dir fail",
	[SH_ERR_PIPE] = "pipe failed",
	[SH_ERR_DUP] = "dup error"
};

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
	if (backup_fds(shell) != SH_SUCCESS)
		return (SH_ERR_DUP);
	return (0);
}

/*
** TODO: print errors
*/

/*
** static void	 print_errors(int ret)
** {
** 	dprintf(2, "42sh: %s\n", g_error_str[ret]);
** }
*/

int			main(int argc, const char **argv, const char **env)
{
	t_sh	shell;
	char	*prompt;
	char	*line;

	if (init_shell(&shell, env))
	{
		free_sh(&shell);
		return (1);
	}
	(void)argc;
	(void)argv;
	prompt = "$> ";
	handle_prompt(&shell, prompt, &line);
	ft_printf("Line: ");
	ft_putnonprint(line);
	ft_putchar('\n');
	free(line);
	free_sh(&shell);
	// ft_printf("executed %s\n", argv[0]);
	return (0);
}
