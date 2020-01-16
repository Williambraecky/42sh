/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_get_from.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:51:28 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/16 01:34:02 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	redir_get_base_fd(t_type type)
{
	if (type == T_GREATER || type == T_GREATER_AND || type == T_DOUBLE_GREATER)
		return (1);
	return (0);
}

int			redir_get_from(t_redir *redir)
{
	if (redir->io_nb)
		return (redir->io_nb->io_nb);
	return (redir_get_base_fd(redir->token->type));
}
