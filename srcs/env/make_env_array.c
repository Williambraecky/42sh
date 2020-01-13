/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:30:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 01:21:15 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		make_env_array(t_sh *shell, char ***array)
{
	t_map	*env_map;
	size_t	len;
	size_t	i;
	size_t	j;

	env_map = shell->env;
	len = ft_mapsize(shell->env);
	if (!(*array = ft_memalloc(sizeof(**array) * (len + 1))))
		return (SH_ERR_MALLOC);
	i = 0;
	j = 0;
	while (i < env_map->max_size)
	{
		if (env_map->nodes[i].is_used)
		{
			if (!((*array)[j++] = ft_strformat("%s=%s", env_map->nodes[i].key,
			(char*)env_map->nodes[i].value)))
			{
				ft_freesplit(*array);
				return (SH_ERR_MALLOC);
			}
		}
		i++;
	}
	return (SH_SUCCESS);
}
