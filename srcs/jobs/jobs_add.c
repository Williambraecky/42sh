/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:55:58 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/10 16:22:19 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "exec.h"

int		jobs_add(t_sh *shell, t_cmd *cmd)
{
	if (ft_vecpush(&shell->jobs, cmd))
		return (SH_ERR_MALLOC);
	ft_printf("[%zu] %d\n", shell->jobs.size + 1, cmd->pgid);
	return (SH_SUCCESS);
}
