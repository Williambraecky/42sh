/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:42:38 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/07 17:57:25 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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
				return (1);
			if (ft_mapputnoclone(shell->env, key, value, ft_strlen(value)))
				return (1);
		}
		i++;
	}
	return (0);
}
