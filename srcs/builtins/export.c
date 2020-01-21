/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:21:03 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 22:15:04 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	print_env(t_map *map)
{
	size_t	i;

	if (!map)
		return ;
	i = 0;
	while (i < map->max_size)
	{
		if (map->nodes[i].is_used)
			ft_printf("%s=%s{eoc}\n", map->nodes[i].key, map->nodes[i].value);
		i++;
	}
}

static int	handle_define(t_sh *shell, char *definition)
{
	char	*equals;

	equals = ft_strchr(definition, '=');
	*equals = '\0';
	if (!str_is_name(definition))
	{
		*equals = '=';
		ft_dprintf(2, "42sh: export: `%s': not a valid identifier\n",
			definition);
		return (1);
	}
	if (repl_env(shell, definition, equals + 1) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

static int	handle_export(t_sh *shell, char *key)
{
	char	*value;

	if (get_internal(shell, key, &value) != SH_SUCCESS)
		value = "";
	if (repl_env(shell, key, value) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

int			export_builtin(int argc, char **argv, t_sh *shell)
{
	size_t	i;
	int		ret;

	if (argc == 1)
		print_env(shell->env);
	i = 1;
	ret = SH_SUCCESS;
	while (i < (size_t)argc)
	{
		if (ft_strchr(argv[i], '=') != NULL)
			ret = handle_define(shell, argv[i]);
		else
			ret = handle_export(shell, argv[i]);
		i++;
	}
	return (ret);
}
