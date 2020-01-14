/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:39:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/14 22:31:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "prompt.h"
#include "lexer.h"
#include "builtin.h"

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

/*
** TODO: Initialize some variables like PS1 ? $ etc
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
	if (ft_vecinit(&shell->jobs))
		return (1);
	if (builtin_init(shell) != SH_SUCCESS)
		return (1);
	add_alias(shell, "ls", "ls -G");
	copy_env(shell, env);
	if ((shell->prompt_mode = isatty(SH_IN)))
		if (init_interactive_mode(shell))
			return (1);
	return (0);
}

/*
** TODO: print errors
*/

/*
** TODO: we need to make sure to retrieve status for jobs in background etc
*/

int			main(int argc, const char **argv, const char **env)
{
	t_sh	shell;
	char	*prompt;
	char	*line;
	t_lexer	lexer_;

	(void)argc;
	(void)argv;
	if (init_shell(&shell, env))
	{
		free_sh(&shell);
		return (1);
	}
	shell.running = 1;
	while (shell.running)
	{
		gen_prompt_string(&shell, "", &prompt);
		handle_prompt(&shell, prompt, &line);
		free(prompt);
		if (lexer(line, &lexer_, &shell) == SH_SUCCESS)
			exec_tree(&shell, lexer_.build.head);
		free(line);
	}
	free_sh(&shell);
	return (0);
}
