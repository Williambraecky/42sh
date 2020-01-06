/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:15:22 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/24 13:29:49 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: defines internal variable + other
*/

static int		valid_arg(char *string)
{
	if (!string || !str_is_name(string))
		return (0);
	else
		return (ft_strchr(string, '=') != NULL);
}

static void		print_internals(t_map *map)
{
	size_t	i;

	if (!map)
		return ;
	i = 0;
	while (i < map->max_size)
	{
		if (map->nodes[i].is_used)
			ft_printf("%s\n", map->nodes[i].value);
		i++;
	}
}

int				set_builtin(int argc, char **argv, t_sh *shell)
{
	char **av;

	if (argc == 1)
		print_internals(shell->internals);
	if (argc == 2 && valid_arg(argv[1]))
	{
		av = ft_strsplit(argv[1], '=');
		if (argc == 2 && has_internal(shell, av[0]))
			return (repl_internal(shell, av[0], av[1]));
		else if (argc == 2 && !has_internal(shell, av[0]))
			return (add_internal(shell, av[0], av[1]));
		ft_freesplit(av);
	}
	return (0);
}
