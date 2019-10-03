/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:27:19 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/13 15:07:13 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_mapclear(t_map *map)
{
	size_t	i;

	if (!map)
		return ;
	i = map->max_size;
	while (i--)
	{
		if (map->nodes[i].is_used)
			ft_memdel(&map->nodes[i].value);
		map->nodes[i].is_used = 0;
	}
	map->size = 0;
}
