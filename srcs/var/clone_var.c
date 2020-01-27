/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 22:41:38 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 22:47:51 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static t_var	*clone_val(t_var *var)
{
	t_var	*new;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (NULL);
	if (!(new->var = ft_strdup(var->var)))
	{
		free(new);
		return (NULL);
	}
	return (new);
}

static int		clone_content(t_map *new, t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->max_size)
	{
		if (map->nodes[i].is_used)
		{
			if (!(new->nodes[i].value = clone_val(map->nodes[i].value)) ||
				!(new->nodes[i].key = ft_strdup(map->nodes[i].key)))
			{
				return (0);
			}
			new->nodes[i].is_used = 1;
			new->nodes[i].size = map->nodes[i].size;
			new->size++;
		}
		i++;
	}
	return (1);
}

t_map			*clone_var(t_sh *shell)
{
	t_map	*new;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (NULL);
	if (!(new->nodes = ft_memalloc(sizeof(t_node) * shell->vars->max_size)))
	{
		free(new);
		return (NULL);
	}
	if (!clone_content(new, shell->vars))
	{
		ft_mapfilter(new, var_del_filter);
		free(new->nodes);
		free(new);
		return (NULL);
	}
	new->size = shell->vars->size;
	new->max_size = shell->vars->max_size;
	return (new);
}
