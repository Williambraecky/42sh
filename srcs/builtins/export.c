/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:21:03 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 22:55:48 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	export_make_array(t_sh *shell, char ***array)
{
	t_map	*vars;
	t_var	*var;
	size_t	i;
	size_t	j;

	vars = shell->vars;
	if (!(*array = ft_memalloc(sizeof(**array) * (count_env(shell) + 1))))
		return (SH_ERR_MALLOC);
	i = 0;
	j = 0;
	while (i < vars->max_size)
	{
		if (vars->nodes[i].is_used)
		{
			var = vars->nodes[i].value;
			if (var->exported && !((*array)[j++] = ft_strformat("%s='%s'",
				vars->nodes[i].key, var->var)))
			{
				ft_freesplit(*array);
				return (SH_ERR_MALLOC);
			}
		}
		i++;
	}
	return (SH_SUCCESS);
}

static void	print_env(t_sh *shell)
{
	char	**array;
	size_t	i;

	if (export_make_array(shell, &array) != SH_SUCCESS)
	{
		ft_dprintf(2, "42sh: export: malloc error\n");
		return ;
	}
	ft_strsort(array, ft_splitlen(array), ft_strcmp);
	i = 0;
	while (array[i])
	{
		ft_printf("%s{eoc}\n", array[i]);
		i++;
	}
	ft_freesplit(array);
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
	t_var	*var;

	if (!str_is_name(key))
	{
		ft_dprintf(2, "42sh: export: `%s': not a valid identifier\n", key);
		return (1);
	}
	if (!has_var(shell, key))
		return (add_env(shell, key, ""));
	var = ft_mapget(shell->vars, key);
	var->exported = 1;
	return (SH_SUCCESS);
}

int			export_builtin(int argc, char **argv, t_sh *shell)
{
	size_t	i;
	int		ret;

	if (argc == 1)
		print_env(shell);
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
