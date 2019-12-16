/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_alias.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:25:04 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 17:34:50 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** HOME: Should alias tokenize or do we do it here?
*/

int		add_alias(t_sh *shell, char *alias, t_vec *tokens)
{
	char	*key_dup;
	char	*alias_dup;
	t_alias	alias_t;

	if (!(key_dup = ft_strdup(alias))
	|| !(alias_dup = ft_strdup(alias)))
		return (SH_ERR_MALLOC);
	alias_t.str = alias_dup;
	alias_t.tokens = tokens;
	if (ft_mapput(shell->aliases, key_dup, &alias_t, sizeof(alias_t)) != MAP_OK)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
