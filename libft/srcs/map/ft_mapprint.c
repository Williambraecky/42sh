/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:56:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/05/07 16:59:58 by rchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_mapprint(t_map *map)
{
	size_t	i;

	if (!map)
		return ;
	ft_printf("Map size %zu; max size %zu\n", map->size, map->max_size);
	i = 0;
	while (i < map->max_size)
	{
		if (map->nodes[i].is_used)
			ft_printf("Node %zu; Key %s; Value %p\n",
			i, map->nodes[i].key, map->nodes[i].value);
		else
			ft_printf("Node %zu unused\n", i);
		i++;
	}
}
