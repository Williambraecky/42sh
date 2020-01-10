/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_bin_built.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:17:11 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/08 19:44:30 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int			get_aliases(t_sh *shell, char *start, t_vec *poss)
{
	size_t	i;
	char	*alias_str;

	i = 0;
	while (i < shell->aliases->max_size)
	{
		if (shell->aliases->nodes[i].is_used)
		{
			alias_str = (char*)shell->aliases->nodes[i].value;
			if (ft_strstartswith(alias_str, start))
				if (ft_veccpush(poss, alias_str, ft_strlen(alias_str) + 1))
					return (SH_ERR_NOEXIST);
		}
		i++;
	}
	return (SH_SUCCESS);
}

/*
** TODO: used shell->builtins for builtin list
**		DONE but check if it works
*/

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
				if (ft_veccpush(poss, built_str, ft_strlen(built_str) + 1))
					return (SH_ERR_NOEXIST);
		}
		i++;
	}
	return (SH_SUCCESS);
}

int					complete_command(t_sh *shell, char *start, t_vec *poss)
{
	char	**path_dir;
	char	*path;
	size_t	i;
	int		ret;

	if (get_env(shell, "PATH", &path) != SH_SUCCESS)
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
	return (get_aliases(shell, start, poss));
}
