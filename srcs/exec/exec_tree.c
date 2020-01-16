/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:44:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/16 01:10:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** NOTE: procedure to execute tree; apply logic etc.
** NOTE: ASSIGNMENTS without command is equal to set builtin
** NOTE: ASSIGNMENTS with command is equal to export only for that command
**    (t_proc)
*/

int		exec_tree(t_sh *shell, t_cmd *tree)
{
	t_cmd	*curr;
	t_cmd	*next;

	curr = tree;
	while (curr)
	{
		next = curr->next;
		if (!curr->condition || curr->condition(get_last_return_code(shell)))
			exec_cmd(shell, curr);
		curr = next;
	}
	return (SH_SUCCESS);
}
