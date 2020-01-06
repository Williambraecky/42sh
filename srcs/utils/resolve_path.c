/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 15:51:35 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/06 11:52:04 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_dir(char *tok, char *name, char **result)
{
	char	*filepath;
	t_stat	stat_t;

	if (!(filepath = ft_strtrijoin(tok, "/", name)))
		return (SH_ERR_MALLOC);
	if (stat(filepath, &stat_t) == 0)
	{
		*result = filepath;
		return (SH_SUCCESS);
	}
	free(filepath);
	return (SH_ERR_NOEXIST);
}

int			resolve_path_env(char *paths, char *name, char **result)
{
	char	*dup;
	char	*tok;
	int		ret;

	if (ft_strchr(name, '/'))
	{
		if (!(*result = ft_strdup(name)))
			return (SH_ERR_MALLOC);
		return (SH_SUCCESS);
	}
	if (!(dup = ft_strdup(paths)))
		return (SH_ERR_MALLOC);
	tok = ft_strtok(dup, ":");
	while (tok)
	{
		if ((ret = check_dir(tok, name, result)) != SH_ERR_NOEXIST)
		{
			free(dup);
			return (ret);
		}
		tok = ft_strtok(NULL, ":");
	}
	free(dup);
	return (SH_ERR_NOEXIST);
}

int			resolve_path(t_sh *shell, char *name, char **result)
{
	char	*paths;
	int		ret;

	if (get_hash_ignorecase(shell, name, result) == SH_SUCCESS)
		return (SH_SUCCESS);
	if ((ret = get_env(shell, "PATH", &paths)) != SH_SUCCESS)
		return (ret);
	return (resolve_path_env(paths, name, result));
}
