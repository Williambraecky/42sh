/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:17:23 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/08 17:25:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		add_env(t_sh *shell, char *key, char *value)
{
	if (!shell->env)
		return (SH_ERR_NOEXIST);
	if (!(key = ft_strdup(key))
		|| !(value = ft_strdup(value)))
		return (SH_ERR_MALLOC);
	if (ft_mapputnoclone(shell->env, key, value, ft_strlen(value)) != MAP_OK)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
