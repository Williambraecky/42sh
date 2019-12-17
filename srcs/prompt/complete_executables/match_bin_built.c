/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_bin_built.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:17:11 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/12/17 18:56:57 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int			get_aliases(t_sh *shell, char *start, t_vec *poss)
{
	size_t	i;
	t_alias	*alias;
	char	*alias_str;

	i = 0;
	while (i < shell->aliases->max_size)
	{
		if (shell->aliases->nodes[i].is_used)
		{
			alias = (t_alias*)shell->aliases->nodes[i].value;
			alias_str = alias->str;
			if (ft_strstartswith(alias_str, start))
				if (ft_vecpush(poss, alias_str))
					return (SH_ERR_NOEXIST);
		}
		i++;
	}
	return (SH_SUCCESS);
}

static int			get_builtin(char **builtin_list, char *start, t_vec *poss)
{
	size_t i;

	i = 0;
	while (builtin_list[i])
	{
		if (ft_strstartswith(builtin_list[i], start))
			if (ft_vecpush(poss, builtin_list[i]))
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
		free(path_dir[i]);
		i++;
	}
	free(path_dir);
	if ((ret = autocomplete_poss(".", start, poss)) != 0)
		return (ret);
	if ((ret = get_builtin(builtin_list, start, poss)) != SH_SUCCESS)
		return (ret);
	return (get_aliases(shell, start, poss));
}
