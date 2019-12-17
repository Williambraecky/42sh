/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:42:38 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 15:54:31 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: Main procedure for copying given env to shell
*/

int		copy_env(t_sh *shell, const char **env)
{
	char	*key;
	char	*value;
	char	*equals;
	size_t	i;

	key = NULL;
	value = NULL;
	i = 0;
	while (env[i])
	{
		if ((equals = ft_strchr(env[i], '=')) != NULL)
		{
			key = ft_strndup((char*)env[i], equals - (char*)env[i]);
			value = ft_strdup(equals + 1);
			if (!key || !value)
				return (SH_ERR_MALLOC);
			if (ft_mapputnoclone(shell->env, key, value, ft_strlen(value))
				!= MAP_OK)
				return (SH_ERR_MALLOC);
		}
		i++;
	}
	return (SH_SUCCESS);
}
