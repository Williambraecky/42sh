/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_map.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:18:28 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/15 16:06:18 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MAP_H
# define LIBFT_MAP_H

# include "libft.h"

# define MAP_DEF_SIZE 10
# define MAP_MAX_COLL 5
# define MAP_OK 0
# define MAP_OMEM 1
# define MAP_FULL -2

typedef struct s_node	t_node;
typedef struct s_map	t_map;

struct		s_node
{
	char	*key;
	int		is_used;
	void	*value;
	size_t	size;
};

struct		s_map
{
	size_t	max_size;
	size_t	size;
	t_node	*nodes;
};

t_map		*ft_mapnew(size_t size);
void		ft_mapclear(t_map *map);
int			ft_mapisempty(t_map *map);
t_map		*ft_mapclone(t_map *map);
void		ft_mapdel(t_map *map);
void		ft_mapremove(t_map *map, char *key);
void		*ft_mapget(t_map *map, char *key);
size_t		ft_mapmaxsize(t_map *map);
size_t		ft_mapsize(t_map *map);
int			ft_mapreplace(t_map *map, char *key, void *value, size_t size);
void		*ft_mapgetordef(t_map *map, char *key, void *def);
t_s64		ft_maphash(t_map *map, char *key);
int			ft_mapputnoclone(t_map *map, char *key, void *value, size_t size);
int			ft_mapput(t_map *map, char *key, void *value, size_t size);
int			ft_maprehash(t_map *map);
void		ft_mapprint(t_map *map);
int			ft_mapcontains(t_map *map, char *key);
void		ft_mapfilter(t_map *map, int (*filter)(t_node *));

#endif
