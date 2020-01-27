/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:17:11 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/27 23:25:09 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int					posscpush(t_vec *poss, char *str, size_t len)
{
	size_t		i;

	i = 0;
	while (i < poss->size)
	{
		if (ft_strequ(ft_vecget(poss, i), str))
			return (0);
		i++;
	}
	return (ft_veccpush(poss, str, len));
}

static int			get_aliases(t_sh *shell, char *start, t_vec *poss)
{
	size_t	i;
	char	*alias_str;

	i = 0;
	while (i < shell->aliases->max_size)
	{
		if (shell->aliases->nodes[i].is_used)
		{
			alias_str = (char*)shell->aliases->nodes[i].key;
			if (ft_strstartswith(alias_str, start))
				if (posscpush(poss, alias_str, ft_strlen(alias_str) + 1))
					return (SH_ERR_NOEXIST);
		}
		i++;
	}
	return (SH_SUCCESS);
}

static int			get_builtin(t_sh *shell, char *start, t_vec *poss)
{
	size_t	i;
	char	*built_str;

	i = 0;
	while (i < shell->builtins->max_size)
	{
		if (shell->builtins->nodes[i].is_used)
		{
			built_str = (char*)shell->builtins->nodes[i].key;
			if (ft_strstartswith(built_str, start))
				if (posscpush(poss, built_str, ft_strlen(built_str) + 1))
					return (SH_ERR_NOEXIST);
		}
		i++;
	}
	return (SH_SUCCESS);
}

int					autocomplete_poss(char *path, char *start, t_vec *poss)
{
	DIR				*dir;
	struct dirent	*sd;

	dir = opendir(path);
	if (dir == NULL)
		return (SH_ERR_OPEN_DIR);
	while ((sd = readdir(dir)) != NULL)
	{
		if (start && ft_strstartswith(sd->d_name, start))
		{
			if ((ft_strequ(sd->d_name, ".") || ft_strequ(sd->d_name, ".."))
			&& ft_strequ("", start))
				continue;
			if (posscpush(poss, sd->d_name, ft_strlen(sd->d_name) + 1))
			{
				closedir(dir);
				return (SH_ERR_MALLOC);
			}
		}
	}
	closedir(dir);
	return (SH_SUCCESS);
}

int					complete_command(t_sh *shell, char *start, t_vec *poss)
{
	char	**path_dir;
	char	*path;
	size_t	i;
	int		ret;

	if (get_var(shell, "PATH", &path) != SH_SUCCESS)
		return (SH_ERR_NOEXIST);
	if (!(path_dir = ft_strsplit(path, ':')))
		return (SH_ERR_MALLOC);
	i = 0;
	while (path_dir[i])
	{
		if ((ret = autocomplete_poss(path_dir[i], start, poss)) != 0)
			return (ret);
		i++;
	}
	ft_freesplit(path_dir);
	if ((ret = get_builtin(shell, start, poss)) != SH_SUCCESS)
		return (ret);
	get_aliases(shell, start, poss);
	return (SH_SUCCESS);
}
