/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_bin_built.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:17:11 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/12/18 14:53:48 by wbraeckm         ###   ########.fr       */
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
				if (ft_veccpush(poss, alias_str, ft_strlen(alias_str)))
					return (SH_ERR_NOEXIST);
		}
		i++;
	}
	return (SH_SUCCESS);
}

/*
** TODO: used shell->builtins for builtin list
*/

static int			get_builtin(char **builtin_list, char *start, t_vec *poss)
{
	size_t i;

	i = 0;
	while (builtin_list[i])
	{
		if (ft_strstartswith(builtin_list[i], start))
			if (ft_veccpush(poss, builtin_list[i], ft_strlen(builtin_list[i])))
				return (SH_ERR_NOEXIST);
		i++;
	}
	return (SH_SUCCESS);
}

int					match_bin_built(t_sh *shell, char **builtin_list,
	char *start, t_vec *poss)
{
	char	**path_dir;
	size_t	i;
	int		ret;

	if (!(path_dir = ft_strsplit(ft_mapget(shell->env, "PATH"), ':')))
		return (SH_ERR_MALLOC);
	i = 0;
	while (path_dir[i])
	{
		if ((ret = autocomplete_poss(path_dir[i], start, poss)) != 0)
			return (ret);
		i++;
	}
	ft_freesplit(path_dir);
	if ((ret = autocomplete_poss(".", start, poss)) != 0)
		return (ret);
	if ((ret = get_builtin(builtin_list, start, poss)) != SH_SUCCESS)
		return (ret);
	return (get_aliases(shell, start, poss));
}
