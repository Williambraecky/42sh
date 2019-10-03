/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:10:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/13 16:35:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_mapget(t_map *map, char *key)
{
	t_s64	hash;

	if (!map)
		return (NULL);
	if ((hash = ft_maphash(map, key)) != MAP_FULL)
	{
		if (map->nodes[hash].is_used)
			return (map->nodes[hash].value);
	}
	return (NULL);
}
