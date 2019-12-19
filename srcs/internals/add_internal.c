/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_internal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:17:23 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/19 15:24:04 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: clones the key and the value
*/

int		add_internal(t_sh *shell, char *key, char *value)
{
	if (!shell->internals)
		return (SH_ERR_NOEXIST);
	if (!(key = ft_strdup(key))
		|| !(value = ft_strdup(value)))
		return (SH_ERR_MALLOC);
	if (ft_mapputnoclone(shell->internals,
		key, value, ft_strlen(value)) != MAP_OK)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
