/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:44:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/10 15:26:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
** NOTE: procedure to execute tree; apply logic etc.
** NOTE: ASSIGNMENTS without command is equal to set builtin
** NOTE: ASSIGNMENTS with command is equal to export only for that command
**    (t_proc)
*/

int		exec_tree(t_sh *shell, t_cmd *tree)
{
	t_cmd	*curr;
	int		last_ret;

	curr = tree;
	last_ret = get_last_return_code(shell);
	while (curr)
	{
		if (!curr->condition || curr->condition(get_last_return_code(shell)))
			last_ret = exec_cmd(shell, curr);
		curr = curr->next;
	}
	(void)shell;
	(void)tree;
	return (SH_SUCCESS);
}
