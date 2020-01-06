/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:15:22 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/06 15:31:51 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: defines internal variable + other
*/

static int	valid_arg(char *string)
{
	if (!string || !str_is_name(string))
		return (0);
	return (SH_SUCCESS);
}

static void	print_internals(t_map *map)
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

int			set_builtin(int argc, char **argv, t_sh *shell)
{
	char	**av;
	size_t	i;
	int		ret;

	if (argc == 1)
		print_internals(shell->internals);
	i = 1;
	ret = SH_SUCCESS;
	while (i < (size_t)argc && ret == SH_SUCCESS)
	{
		if (ft_strchr(argv[i], '=') != NULL)
		{
			av = ft_strsplit(argv[i], '=');
			if (!valid_arg(av[0]))
				return (SH_ERR_SYNTAX);
			ret = repl_internal(shell, av[0], av[1]);
			ft_freesplit(av);
		}
		++i;
	}
	return (ret);
}
