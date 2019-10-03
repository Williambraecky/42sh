/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:23:45 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/13 15:59:21 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_mapremove(t_map *map, char *key)
{
	t_s64	hash;

	if (!map)
		return ;
	if ((hash = ft_maphash(map, key)) != MAP_FULL)
	{
		if (map->nodes[hash].is_used)
		{
			map->nodes[hash].is_used = 0;
			ft_memdel(&map->nodes[hash].value);
			map->size--;
		}
	}
}
