/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:28:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/18 14:19:03 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

/*
** NOTE: assumes aliases are vectors
*/

int		remove_alias(t_sh *shell, char *alias)
{
	t_s64	hash;

	if (!has_alias(shell, alias))
		return (SH_SUCCESS);
	if ((hash = ft_maphash(shell->aliases, alias)) != MAP_FULL)
	{
		if (shell->aliases->nodes[hash].is_used)
		{
			shell->aliases->nodes[hash].is_used = 0;
			ft_memdel(&shell->aliases->nodes[hash].value);
			ft_strdel(&shell->aliases->nodes[hash].key);
			shell->aliases->size--;
		}
	}
	return (SH_SUCCESS);
}
