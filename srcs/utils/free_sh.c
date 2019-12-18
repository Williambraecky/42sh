/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:49:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/18 16:12:45 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

/*
** NOTE: Main shell free procedure add fields to be freed here
*/

static int	map_del_filter(t_node *node)
{
	free(node->key);
	free(node->value);
	return (0);
}

/*
** NOTE: we might need to move the signal stuff right after stopping the prompt
**  as we do need to reset it anywayy before executing anything
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
	ft_mapdel(shell->builtins);
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
}
