/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:44:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 23:48:12 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: should print what type something is
**   order is alias -> builtin -> executable
*/

static int	check_is_alias(char *name, t_sh *shell)
{
	if (has_alias(shell, name))
	{
		ft_printf("%s is an alias for '%s'\n", name, get_alias(shell, name));
		return (-1);
	}
	return (0);
}

static int	check_is_builtin(char *name, t_sh *shell)
{
	if (is_builtin(shell, name))
	{
		ft_printf("%s is a shell builtin\n", name);
		return (-1);
	}
	return (0);
}

static int	check_is_exec(char *name, t_sh *shell)
{
	char	*path;
	t_stat	stat_t;

	if (resolve_path(shell, name, &path) == SH_SUCCESS)
	{
		if (stat(path, &stat_t) == 0 && !S_ISDIR(stat_t.st_mode) &&
			access(path, X_OK) == 0)
		{
			ft_printf("%s is %s\n", name, path);
			free(path);
			return (-1);
		}
		free(path);
	}
	return (0);
}

int			type_builtin(int ac, char **av, t_sh *shell)
{
	size_t	i;
	int		ret;

	i = 1;
	ret = 0;
	while (i < (size_t)ac)
	{
		if (ret > 0)
			return (ret);
		if ((ret = check_is_alias(av[i], shell)) && i++)
			continue;
		if ((ret = check_is_builtin(av[i], shell)) && i++)
			continue;
		if ((ret = check_is_exec(av[i], shell)) && i++)
			continue;
		ft_printf("%s not found\n", av[i]);
		i++;
	}
	return (SH_SUCCESS);
}
