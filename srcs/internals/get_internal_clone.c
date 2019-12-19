/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_internal_clone.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:14:38 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/19 15:24:39 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: get_env but clones the result to *result
*/

int		get_internal_clone(t_sh *shell, char *key, char **result)
{
	if (!shell->internals)
		return (SH_ERR_NOEXIST);
	if (!(*result = ft_mapget(shell->internals, key)))
		return (SH_ERR_ENV_NOEXIST);
	if (!(*result = ft_strdup(*result)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
