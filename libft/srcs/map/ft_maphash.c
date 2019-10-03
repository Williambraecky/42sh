/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maphash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:40:59 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/13 16:35:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_s64	ft_maphash(t_map *map, char *key)
{
	size_t	i;
	t_u64	hash;

	if (map->size >= map->max_size)
		return (MAP_FULL);
	hash = ft_strhash(key) % map->max_size;
	i = 0;
	while (i < MAP_MAX_COLL)
	{
		if (!map->nodes[hash].is_used ||
			ft_strequ(map->nodes[hash].key, key))
			return ((t_s64)hash);
		hash = (hash + 1) % map->max_size;
		i++;
	}
	return (MAP_FULL);
}
