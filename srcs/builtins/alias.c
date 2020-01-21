/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:01:51 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 21:12:17 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

static void	display(t_sh *shell, char **sorted_al)
{
	size_t	i;

	if (!sorted_al)
		return ;
	i = 0;
	while (sorted_al[i])
	{
		ft_printf("%s='%s'\n", sorted_al[i], get_alias(shell, sorted_al[i]));
		++i;
	}
}

static int	print_aliases(t_sh *shell, t_map *al)
{
	char	**array;
	size_t	i;
	size_t	j;
	int		len;

	len = shell->aliases->size;
	if (!(array = (char **)ft_memalloc(sizeof(char *) * (len + 1))))
		return (SH_ERR_MALLOC);
	i = al->max_size;
	j = 0;
	while (i--)
	{
		if (al->nodes[i].is_used && j < (size_t)len)
		{
			if (!(array[j++] = al->nodes[i].key))
			{
				free(array);
				return (SH_ERR_MALLOC);
			}
		}
	}
	ft_strsort(array, j, &ft_strcmp);
	display(shell, array);
	free(array);
	return (SH_SUCCESS);
}

static int	handle_define(t_sh *shell, char *definition)
{
	char	*equals;

	equals = ft_strchr(definition, '=');
	*equals = '\0';
	if (repl_alias(shell, definition, equals + 1) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

static int	handle_print(t_sh *shell, char *alias)
{
	char	*aliased;

	aliased = get_alias(shell, alias);
	if (!aliased)
	{
		ft_dprintf(2, "42sh: alias: %s: not found\n", alias);
		return (1);
	}
	ft_printf("%s='%s'\n", alias, aliased);
	return (0);
}

int			alias_builtin(int argc, char **argv, t_sh *shell)
{
	size_t	i;
	int		err;
	int		ret;

	if (argc == 1)
		return (print_aliases(shell, shell->aliases));
	i = 1;
	ret = SH_SUCCESS;
	err = 0;
	while (i < (size_t)argc && ret == SH_SUCCESS)
	{
		if (ft_strchr(argv[i], '=') != NULL)
			ret = handle_define(shell, argv[i]);
		else
			err = handle_print(shell, argv[i]);
		i++;
	}
	if (ret != SH_SUCCESS)
		return (ret);
	return (err);
}
