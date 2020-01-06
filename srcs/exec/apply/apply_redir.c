/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:19:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/06 15:39:46 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	new_redir(t_token *token, t_build *build)
{
	t_redir	redir;

	redir.token = token;
	redir.io_nb = NULL;
	redir.filename = NULL;
	if (ft_veccpush(&build->work_proc->redirections, &redir, sizeof(redir)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

int			apply_redir(t_token *token, t_build *build)
{
	t_redir	*top;

	if (build->expected_type && !(build->expected_type & (1 << token->type)))
		return (SH_ERR_SYNTAX);
	if ((top = (t_redir*)ft_vecgettop(&build->work_proc->redirections))
		&& top->token == NULL)
		top->token = token;
	else
		return (new_redir(token, build));
	return (SH_SUCCESS);
}
