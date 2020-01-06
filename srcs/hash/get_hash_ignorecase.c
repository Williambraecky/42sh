/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hash_ignorecase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 11:42:59 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/06 11:50:59 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_hash_ignorecase(t_sh *shell, char *str, char **result)
{
	size_t		i;
	t_hashed	*hashed;

	if (!shell->use_hash)
		return (SH_ERR_NOEXIST);
	i = 0;
	while (i < shell->use_hash->max_size)
	{
		if (shell->use_hash->nodes[i].is_used)
		{
			hashed = (t_hashed*)shell->use_hash->nodes[i].value;
			if (ft_strequignorecase(shell->use_hash->nodes[i].key, str))
			{
				*result = hashed->path;
				return (SH_SUCCESS);
			}
		}
		i++;
	}
	return (SH_ERR_NOEXIST);
}
