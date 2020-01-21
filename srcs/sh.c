/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:39:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 23:24:52 by wbraeckm         ###   ########.fr       */
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

static int	init_shell(t_sh *shell, const char **env)
{
	ft_memset(shell, 0, sizeof(*shell));
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
	if (init_internal_vars(shell))
		return (1);
	add_alias(shell, "ls", "ls -G");
	if (copy_env(shell, env) != SH_SUCCESS)
		return (1);
	if (init_history(shell) != SH_SUCCESS)
		return (1);
	if ((shell->prompt_mode = isatty(SH_IN)))
		if (init_interactive_mode(shell))
			return (1);
	return (0);
}

int			run_command(t_sh *shell, char *command)
{
	t_lexer	lexer_;
	int		ret;

	ft_bzero(&lexer_, sizeof(lexer_));
	if ((ret = lexer(command, &lexer_, shell)) == SH_SUCCESS)
	{
		shell->allow_hash_update = 1;
		exec_tree(shell, lexer_.build.head);
		shell->allow_hash_update = 0;
	}
	else
		free_tree(lexer_.build.head);
	if (ret != SH_ERR_MALLOC)
		add_history(shell, lexer_.clean_line);
	lexer_free(&lexer_);
	return (ret);
}

/*
** TODO: print errors
** TODO: handle event substitution
*/

static void	run(t_sh *shell)
{
	char	*prompt;
	char	*line;
	char	*ps1;
	int		ret;

	get_internal(shell, "PS1", &ps1);
	gen_prompt_string(shell, ps1, &prompt);
	ret = handle_prompt(shell, prompt, &line);
	free(prompt);
	if (ret == SH_SUCCESS && ft_strchr(line, '!'))
	{
		if ((ret = substitute_event(shell, line, &prompt)) == SH_SUCCESS)
		{
			if (!ft_strequ(line, prompt))
				ft_dprintf(0, "%s", prompt);
			free(line);
			line = prompt;
		}
	}
	job_notify(shell);
	if (ret == SH_SUCCESS)
	{
		run_command(shell, line);
		usleep(50000);
		job_notify(shell);
	}
	free(line);
}

int			main(int argc, const char **argv, const char **env)
{
	t_sh	shell;

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
		run(&shell);
	}
	free_sh(&shell);
	return (shell.stop_code);
}
