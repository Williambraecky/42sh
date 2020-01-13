/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:17:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 18:02:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		cmd_is_empty(t_cmd *cmd)
{
	if (!cmd || !cmd->pipeline)
		return (1);
	return (proc_is_empty(cmd->pipeline));
}
