/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:37:25 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/04/24 19:15:59 by rchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_mapput(t_map *map, char *key, void *value, size_t size)
{
	t_s64	hash;

	if (!map)
		return (MAP_FULL);
	hash = ft_maphash(map, key);
	while (hash == MAP_FULL)
	{
		if (ft_maprehash(map) == MAP_OMEM)
			return (MAP_OMEM);
		hash = ft_maphash(map, key);
	}
	if (!(map->nodes[hash].value = ft_memdup(value, size)))
	{
		map->nodes[hash].is_used = 0;
		return (MAP_OMEM);
	}
	map->nodes[hash].key = key;
	map->nodes[hash].is_used = 1;
	map->nodes[hash].size = size;
	map->size++;
	return (MAP_OK);
}
