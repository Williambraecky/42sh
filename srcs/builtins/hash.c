/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:21:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/08 18:38:06 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: prints executables currently in hash list (with usage)
*/

static int	check_in_path_dir(DIR *dir, char *name)
{
	struct dirent	*sd;

	while ((sd = readdir(dir)) != NULL)
	{
		if (ft_strequ(name, sd->d_name))
			return (0);
	}
	return (1);
}

static int	is_binary(char *name, t_sh *shell)
{
	DIR		*dir;
	char	*path;
	char	**path_dir;
	size_t	i;
	int		ret;

	if (get_env(shell, "PATH", &path) != SH_SUCCESS
	|| !(path_dir = ft_strsplit(path, ':')))
		return (has_env(shell, "PATH") ? SH_ERR_ENV_NOEXIST : SH_ERR_MALLOC);
	i = 0;
	while (path_dir[i])
	{
		dir = opendir(path_dir[i]);
		if (dir == NULL)
			return (SH_ERR_OPEN_DIR);
		if ((ret = check_in_path_dir(dir, name)) == 0)
			return (ret);
		i++;
	}
	return (SH_ERR_NOEXIST);
}

static int	print_hash_table(char **av, t_sh *shell)
{
	size_t		i;
	int			ret;
	t_hashed	*hash;

	i = 1;
	while (av[i])
	{
		if ((ret = is_binary(av[i], shell)) > 0)
			return (ret);
		i++;
		if (!av[i])
			return (SH_SUCCESS);
	}
	if (shell->use_hash->max_size < 1)
		return (SH_SUCCESS);
	i = 0;
	while (i < shell->use_hash->max_size)
	{
		if (shell->use_hash->nodes[i].is_used)
			get_hash(shell, shell->use_hash->nodes[i].value, &hash);
		ft_printf("%d\t%s", hash->uses, hash->path);
		i++;
	}
	return (SH_SUCCESS);
}

static int	clear_hash_table(char **av, t_sh *shell)
{
	size_t	i;
	int		ret;

	i = 0;
	while (i < shell->use_hash->max_size)
	{
		if (shell->use_hash->nodes[i].is_used)
			remove_hash(shell, shell->use_hash->nodes[i].key);
		i++;
	}
	i = 2;
	while (av[i])
	{
		if ((ret = is_binary(av[i], shell)) > 0)
			return (ret);
		i++;
	}
	return (SH_SUCCESS);
}

int			hash_builtin(int ac, char **av, t_sh *shell)
{
	int		r_flg;
	size_t	i;

	r_flg = 0;
	i = 1;
	while (i < (size_t)ac && av[i] && av[i][0] == '-')
	{
		if (ft_strequ("-r", av[i]))
			r_flg = 1;
		else
		{
			ft_printf("42sh: hash: -%c: invalid option\n", av[i][1]);
			ft_printf("usage: hash [-r] [name...]\n");
			return (SH_SUCCESS);
		}
		i++;
	}
	if (r_flg)
		return (clear_hash_table(av, shell));
	else
		return (print_hash_table(av, shell));
	return (SH_SUCCESS);
}
