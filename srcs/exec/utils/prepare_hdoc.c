/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_hdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 22:34:28 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/25 21:14:55 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		prepare_hdoc(t_sh *shell, t_hdoc *doc)
{
	char	*new;
	int		ret;

	if (pipe(doc->pipe) != 0)
		return (SH_ERR_PIPE);
	if ((ret = substitute(shell, doc->content, &new, SUB_PARAM)) != SH_SUCCESS)
	{
		close(doc->pipe[0]);
		close(doc->pipe[1]);
		return (ret);
	}
	write(doc->pipe[1], new, ft_strlen(new));
	free(new);
	close(doc->pipe[1]);
	return (SH_SUCCESS);
}
