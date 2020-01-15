/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:49:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 02:04:07 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

/*
** NOTE: Main shell free procedure add fields to be freed here
*/

static int	map_hash_filter(t_node *node)
{
	t_hashed	*hashed;

	hashed = node->value;
	free(hashed->path);
	free(node->value);
	free(node->key);
	return (0);
}

int			map_del_filter(t_node *node)
{
	free(node->key);
	free(node->value);
	return (0);
}

/*
** TODO: actually do it lol
*/

static void	jobs_destroy(t_cmd **cmd)
{
	(void)cmd;
}

/*
** NOTE: we might need to move the signal stuff right after stopping the prompt
**  as we do need to reset it anywayy before executing anything
** TODO: this should be done in the prompt code
*/

void		free_sh(t_sh *shell)
{
	struct sigaction action;

	ft_mapfilter(shell->internals, map_del_filter);
	ft_mapdel(shell->internals);
	ft_mapfilter(shell->env, map_del_filter);
	ft_mapdel(shell->env);
	ft_mapfilter(shell->aliases, map_del_filter);
	ft_mapdel(shell->aliases);
	ft_mapfilter(shell->use_hash, map_hash_filter);
	ft_mapdel(shell->use_hash);
	ft_mapdel(shell->builtins);
	ft_vecdestroy(&shell->jobs, jobs_destroy);
	ft_vecdestroy(&shell->history, default_vec_destroy_function);
	if (shell->prompt_mode)
	{
		tcsetattr(SH_IN, TCSADRAIN, &shell->old_termios);
		ft_memset(&action, 0, sizeof(action));
		action.sa_handler = SIG_DFL;
		sigaction(SIGINT, &action, NULL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
		signal(SIGWINCH, SIG_DFL);
	}
	ft_bzero(shell, sizeof(*shell));
}
