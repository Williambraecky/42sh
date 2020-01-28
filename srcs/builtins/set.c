/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:15:22 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/28 13:58:45 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: defines internal variable + other
*/

static int	set_make_array(t_sh *shell, char ***array)
{
	t_map	*vars;
	t_var	*var;
	size_t	i;
	size_t	j;

	vars = shell->vars;
	if (!(*array = ft_memalloc(sizeof(**array) * (vars->size + 1))))
		return (SH_ERR_MALLOC);
	i = 0;
	j = 0;
	while (i < vars->max_size)
	{
		if (vars->nodes[i].is_used)
		{
			var = (t_var*)vars->nodes[i].value;
			if (!((*array)[j++] = ft_strformat("%s='%s'",
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

static void	print_vars(t_sh *shell)
{
	char	**array;
	size_t	i;

	if (set_make_array(shell, &array) != SH_SUCCESS)
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
		ft_dprintf(2, "42sh: set: `%s': not a valid identifier\n",
			definition);
		return (1);
	}
	if (repl_var(shell, definition, equals + 1) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

int			set_builtin(int argc, char **argv, t_sh *shell)
{
	size_t	i;
	int		ret;

	if (argc == 1)
		print_vars(shell);
	i = 1;
	ret = SH_SUCCESS;
	while (i < (size_t)argc)
	{
		if (ft_strchr(argv[i], '=') != NULL)
			ret = handle_define(shell, argv[i]);
		i++;
	}
	return (ret);
}
