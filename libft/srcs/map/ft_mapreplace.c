/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:28:54 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/13 15:59:31 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_mapreplace(t_map *map, char *key, void *value, size_t size)
{
	t_s64	hash;

	if (!map)
		return (MAP_OMEM);
	if ((hash = ft_maphash(map, key)) != MAP_FULL)
	{
		if (map->nodes[hash].is_used)
		{
			ft_memdel(&map->nodes[hash].value);
			if (!(map->nodes[hash].value = ft_memdup(value, size)))
			{
				map->nodes[hash].is_used = 0;
				map->size--;
				return (MAP_OMEM);
			}
		}
	}
	return (MAP_OK);
}
