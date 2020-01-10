/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:17:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/10 15:25:15 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		cmd_is_empty(t_cmd *cmd)
{
	if (!cmd || !cmd->pipeline)
		return (1);
	return (proc_is_empty(cmd->pipeline));
}
