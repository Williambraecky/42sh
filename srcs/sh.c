/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:39:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 19:44:03 by wbraeckm         ###   ########.fr       */
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

char		*g_history_test[] =
{
	"ls",
	"echo salut les amis",
	"echo coucou",
	"cat",
	"cd ~/Documents",
	NULL
};

static int	fill_shell_history(t_sh *shell)
{
	size_t	i;

	i = 0;
	if (ft_vecinit(&shell->history))
		return (1);
	while (g_history_test[i])
	{
		if (ft_veccpush(&shell->history, g_history_test[i],
			ft_strlen(g_history_test[i]) + 1))
			return (1);
		i++;
	}
	return (0);
}

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
	if (fill_shell_history(shell))
		return (1);
	if (init_internal_vars(shell))
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
	char	*ps1;
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
		get_internal(&shell, "PS1", &ps1);
		gen_prompt_string(&shell, ps1, &prompt);
		handle_prompt(&shell, prompt, &line);
		job_notify(&shell);
		free(prompt);
		if (lexer(line, &lexer_, &shell) == SH_SUCCESS)
		{
			ft_vecpush(&shell.history, ft_strndup(lexer_.clean_line,
				ft_strlen(lexer_.clean_line) - 1));
			exec_tree(&shell, lexer_.build.head);
			usleep(50000);
			job_notify(&shell);
		}
		free(line);
	}
	free_sh(&shell);
	return (0);
}
