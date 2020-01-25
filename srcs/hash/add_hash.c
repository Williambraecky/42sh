/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:21:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/25 23:09:44 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		add_hash(t_sh *shell, char *cmd, char *path)
{
	t_hashed	hashed;
	char		*key_dup;
	char		*path_dup;

	if (!shell->use_hash || !shell->allow_hash_update)
		return (SH_SUCCESS);
	key_dup = NULL;
	path_dup = NULL;
	if (!(key_dup = ft_strdup(cmd)) ||
		!(path_dup = ft_strdup(path)))
	{
		free(key_dup);
		free(path_dup);
		return (SH_ERR_MALLOC);
	}
	hashed.uses = 0;
	hashed.path = path_dup;
	if (ft_mapput(shell->use_hash, key_dup, &hashed, sizeof(hashed)) != MAP_OK)
	{
		free(key_dup);
		free(path_dup);
		return (SH_ERR_MALLOC);
	}
	return (SH_SUCCESS);
}
