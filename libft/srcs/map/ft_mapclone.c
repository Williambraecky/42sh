/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapclone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:28:45 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 13:54:19 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	clone_content(t_map *new, t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->max_size)
	{
		if (map->nodes[i].is_used)
		{
			if (!(new->nodes[i].value =
				ft_memdup(map->nodes[i].value, map->nodes[i].size)) ||
				!(new->nodes[i].key = ft_strdup(map->nodes[i].key)))
			{
				while (i--)
				{
					ft_memdel(&new->nodes[i].value);
					ft_strdel(&new->nodes[i].key);
				}
				return (0);
			}
		}
		i++;
	}
	return (1);
}

t_map		*ft_mapclone(t_map *map)
{
	t_map	*new;

	if (!map || !(new = ft_memalloc(sizeof(*new))))
		return (NULL);
	if (!(new->nodes = ft_memdup(map->nodes, sizeof(t_node) * map->max_size)))
	{
		free(new);
		return (NULL);
	}
	if (!clone_content(new, map))
	{
		free(new->nodes);
		free(new);
		return (NULL);
	}
	new->size = map->size;
	new->max_size = map->max_size;
	return (new);
}
