/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapputnoclone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:56:02 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/13 16:54:44 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_mapputnoclone(t_map *map, char *key, void *value, size_t size)
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
	map->nodes[hash].value = value;
	map->nodes[hash].key = key;
	map->nodes[hash].is_used = 1;
	map->nodes[hash].size = size;
	map->size++;
	return (MAP_OK);
}
