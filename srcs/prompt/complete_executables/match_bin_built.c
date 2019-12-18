/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_bin_built.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:17:11 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/12/18 17:22:41 by mpizzaga         ###   ########.fr       */
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
**		DONE but check if it works
*/

static int			get_builtin(t_sh *shell, char *start, t_vec *poss)
{
	size_t	i;
	char	*built_str;

	i = 0;
	built_str = shell->builtins->nodes[i].value;
	while (shell->builtins->max_size)
	{
		if (shell->builtins->nodes[i].is_used)
		{
			built_str = (char*)shell->builtins->nodes[i].value;
			if (ft_strstartswith(built_str, start))
				if (ft_veccpush(poss, built_str, ft_strlen(built_str)))
					return (SH_ERR_NOEXIST);
		}
		i++;
	}
	return (SH_SUCCESS);
}

int					match_bin_built(t_sh *shell, char *start, t_vec *poss)
{
	char	**path_dir;
	size_t	i;
	int		ret;

	if (!(path_dir = ft_strsplit(ft_mapget(shell->env, "PATH"), ':')))
		return (SH_ERR_MALLOC);//peut segfault si unsetenv PATH (use getenv)
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
	if ((ret = get_builtin(shell, start, poss)) != SH_SUCCESS)
		return (ret);
	return (get_aliases(shell, start, poss));
}
