/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:11:59 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/16 03:04:51 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** NOTE: backgrounded cmds are freed by the job control
*/

void		free_tree(t_cmd *cmd)
{
	t_cmd	*curr;
	t_cmd	*next;

	curr = cmd;
	while (curr)
	{
		next = curr->next;
		free_cmd(curr);
		curr = next;
	}
}
