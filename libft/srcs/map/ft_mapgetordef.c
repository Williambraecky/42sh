/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapgetordef.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:34:01 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/13 15:51:46 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_mapgetordef(t_map *map, char *key, void *def)
{
	t_s64	hash;

	if (!map)
		return (def);
	if ((hash = ft_maphash(map, key)) != MAP_FULL)
	{
		if (map->nodes[hash].is_used)
			return (map->nodes[hash].value);
	}
	return (def);
}
