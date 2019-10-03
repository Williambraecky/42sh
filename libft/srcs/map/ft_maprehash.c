/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maprehash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:35:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/13 17:00:45 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_maprehash(t_map *map)
{
	t_node	*old;
	size_t	i;
	int		status;

	old = map->nodes;
	if (!(map->nodes = ft_calloc(map->max_size * 2, sizeof(t_node))))
	{
		map->nodes = old;
		return (MAP_OMEM);
	}
	i = map->max_size;
	map->max_size *= 2;
	map->size = 0;
	while (i--)
	{
		if (old[i].is_used)
			if ((status = ft_mapputnoclone(map, old[i].key,
				old[i].value, old[i].size)) != MAP_OK)
			{
				free(old);
				return (status);
			}
	}
	free(old);
	return (MAP_OK);
}
