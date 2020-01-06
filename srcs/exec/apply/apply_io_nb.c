/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_io_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:20:15 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/06 15:39:11 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		apply_io_nb(t_token *token, t_build *build)
{
	t_redir	redir;

	if (build->expected_type && !(build->expected_type & (1 << token->type)))
		return (SH_ERR_SYNTAX);
	redir.io_nb = (t_io_nb*)token;
	redir.filename = NULL;
	redir.token = NULL;
	if (ft_veccpush(&build->work_proc->redirections, &redir, sizeof(redir)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
