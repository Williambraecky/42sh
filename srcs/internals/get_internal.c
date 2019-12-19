/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_internal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:13:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/19 15:26:20 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_internal(t_sh *shell, char *key, char **result)
{
	if (!shell->internals)
		return (SH_ERR_NOEXIST);
	if (!(*result = ft_mapget(shell->internals, key)))
		return (SH_ERR_ENV_NOEXIST);
	return (SH_SUCCESS);
}
