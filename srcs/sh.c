/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:39:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/05 14:44:04 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "prompt.h"
#include "lexer.h"
#include "builtin.h"

static int	init_shell(t_sh *shell, const char **env)
{
	ft_memset(shell, 0, sizeof(*shell));
	if (!(shell->vars = ft_mapnew(100)) ||
		!(shell->aliases = ft_mapnew(10)) ||
		!(shell->builtins = ft_mapnew(30)) ||
		!(shell->use_hash = ft_mapnew(30)))
		return (1);
	if (ft_vecinit(&shell->jobs))
		return (1);
	if (builtin_init(shell) != SH_SUCCESS)
		return (1);
	if (init_internal_vars(shell))
		return (1);
	if (init_aliases(shell))
		return (1);
	if (copy_env(shell, env) != SH_SUCCESS)
		return (1);
	if (init_history(shell) != SH_SUCCESS)
		return (1);
	shell->pid = getpid();
	if (has_var(shell, "TERM") && (shell->interactive_mode = isatty(SH_IN)))
		if (init_interactive_mode(shell))
			return (1);
	return (0);
}

/*
** TODO: differentiate between critical return code and non critical
*/

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
	if (ret != SH_ERR_MALLOC && shell->interactive_mode)
		add_history(shell, lexer_.clean_line);
	lexer_free(&lexer_);
	return (ret);
}

static int	do_event_subst(t_sh *shell, char **line)
{
	char	*new;
	int		ret;

	ret = SH_SUCCESS;
	if (ft_strchr(*line, '!'))
	{
		if ((ret = substitute_event(shell, *line, &new)) == SH_SUCCESS)
		{
			if (!ft_strequ(*line, new))
				ft_dprintf(0, "%s", new);
			free(*line);
			*line = new;
		}
	}
	return (ret);
}

/*
** TODO: print errors
*/

static int	run(t_sh *shell)
{
	char	*prompt;
	char	*line;
	char	*ps1;
	int		ret;

	get_var(shell, "PS1", &ps1);
	gen_prompt_string(shell, ps1, &prompt);
	ret = handle_prompt(shell, prompt, &line);
	free(prompt);
	if (ret == SH_SUCCESS && ft_strchr(line, '!'))
		ret = do_event_subst(shell, &line);
	job_notify(shell);
	if (ret == SH_SUCCESS)
		ret = run_command(shell, line);
	usleep(50000);
	job_notify(shell);
	shell->block_history = 0;
	free(line);
	return (ret);
}

int			main(int argc, const char **argv, const char **env)
{
	t_sh			shell;
	int				stop_code;
	struct timeval	time;
	int				ret;

	(void)argc;
	(void)argv;
	gettimeofday(&time, NULL);
	srand(time.tv_usec);
	if (init_shell(&shell, env))
	{
		free_sh(&shell);
		return (1);
	}
	shell.running = 1;
	ret = SH_SUCCESS;
	while (shell.running && ret != SH_ERR_MALLOC && ret != SH_READ_DONE)
		ret = run(&shell);
	if (ret == SH_ERR_MALLOC)
		ft_dprintf(2, "42sh: malloc error (exiting)\n");
	stop_code = shell.stop_code;
	free_sh(&shell);
	return (stop_code);
}
