/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:19:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/13 16:24:34 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_map	*ft_mapnew(size_t size)
{
	t_map	*map;

	if (!(map = ft_memalloc(sizeof(*map))))
		return (NULL);
	if (!size)
		size = MAP_DEF_SIZE;
	map->max_size = size;
	if (!(map->nodes = ft_calloc(size, sizeof(t_node))))
	{
		free(map);
		return (NULL);
	}
	return (map);
}
