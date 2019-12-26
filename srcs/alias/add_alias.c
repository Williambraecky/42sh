/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_alias.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:25:04 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/26 21:53:01 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** HOME: Should alias tokenize or do we do it here?
*/

int		add_alias(t_sh *shell, char *alias, char *aliased)
{
	char	*key_dup;

	if (!(key_dup = ft_strdup(alias)))
		return (SH_ERR_MALLOC);
	if (ft_mapput(shell->aliases, key_dup, aliased, ft_strlen(aliased) + 1)
			!= MAP_OK)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
