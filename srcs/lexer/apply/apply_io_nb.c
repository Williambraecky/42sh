/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_io_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:20:15 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 22:40:59 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		apply_io_nb(t_token *token, t_build *build, t_lexer *lexer)
{
	t_redir	redir;

	(void)lexer;
	redir.io_nb = (t_io_nb*)token;
	redir.filename = NULL;
	redir.token = NULL;
	if (ft_veccpush(&build->work_proc->redirections, &redir, sizeof(redir)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
