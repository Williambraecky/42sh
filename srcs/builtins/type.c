/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:44:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/18 17:44:22 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: should print what type something is
**   order is alias -> builtin -> executable
*/

static int	check_is_alias(char *name, t_sh *shell)
{
	size_t	i;
	char	*alias_value;
	char	*alias_key;

	i = 0;
	while (i < shell->aliases->max_size)
	{
		if (shell->aliases->nodes[i].is_used)
		{
			alias_value = (char*)shell->aliases->nodes[i].value;
			alias_key = (char*)shell->aliases->nodes[i].key;
			if (ft_strequ(alias_key, name))
			{
				ft_printf("%s is an alias for %s\n", alias_key, alias_value);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

static int	check_is_builtin(char *name, t_sh *shell)
{
	size_t	i;
	char	*built_key;

	i = 0;
	while (i < shell->builtins->max_size)
	{
		if (shell->builtins->nodes[i].is_used)
		{
			built_key = (char*)shell->builtins->nodes[i].key;
			if (ft_strequ(built_key, name))
			{
				ft_printf("%s is a shell builtin\n", name);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

static int	check_inside_path_dir(DIR *dir, char *name, char *path)
{
	struct dirent	*sd;

	while ((sd = readdir(dir)) != NULL)
	{
		if (ft_strequ(name, sd->d_name))
		{
			ft_printf("%s is %s/%s\n", name, path, name);
			return (-1);
		}
	}
	return (0);
}

static int	check_is_exec(char *name, t_sh *shell)
{
	char 	**path_dir;
	size_t 	i;
	int		ret;
	DIR		*dir;

	if (!(path_dir = ft_strsplit(ft_mapget(shell->env, "PATH"), ':')))
		return (SH_ERR_MALLOC);//peut segfault si unsetenv PATH (use getenv)
	i = 0;
	while (path_dir[i])
	{
		dir = opendir(path_dir[i]);
		if (dir == NULL)
			return (SH_ERR_OPEN_DIR);
		ret = check_inside_path_dir(dir, name, path_dir[i]);
		if (ret)
			return (ret);
		i++;
	}
	ft_freesplit(path_dir);
	closedir(dir);
	return (0);
}

int			type_builtin(int ac, char **av, t_sh *shell)
{
	size_t 	i;
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
