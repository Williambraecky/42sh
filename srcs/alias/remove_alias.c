/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:28:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 15:09:16 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

/*
** NOTE: assumes aliases are vectors
*/

int		remove_alias(t_sh *shell, char *alias)
{
	t_alias	*alias_t;

	if (!has_alias(shell, alias))
		return (SH_SUCCESS);
	if (!(alias_t = ft_mapget(shell->aliases, alias)))
		return (SH_ERR_NOEXIST);
	ft_strdel(&alias_t->str);
	ft_vecdestroy(alias_t->tokens, token_free);
	ft_mapremove(shell->aliases, alias);
	return (SH_SUCCESS);
}
