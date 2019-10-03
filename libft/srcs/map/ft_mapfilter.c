/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapfilter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 15:55:14 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/05/18 15:57:50 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** filter function pointer should return 0 if the element should be removed
*/

void	ft_mapfilter(t_map *map, int (*filter)(t_node *))
{
	size_t	i;

	if (!map)
		return ;
	i = map->max_size;
	while (i--)
	{
		if (map->nodes[i].is_used)
		{
			if (!filter(&map->nodes[i]))
			{
				map->nodes[i].is_used = 0;
				map->size--;
			}
		}
	}
}
