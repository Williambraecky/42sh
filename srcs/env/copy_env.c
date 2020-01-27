/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:42:38 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 22:38:29 by wbraeckm         ###   ########.fr       */
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

	i = 0;
	while (env[i])
	{
		if ((equals = ft_strchr(env[i], '=')) != NULL)
		{
			key = (char*)env[i];
			*equals = '\0';
			value = equals + 1;
			if (add_env(shell, key, value) != SH_SUCCESS)
				return (SH_ERR_MALLOC);
			*equals = '=';
		}
		i++;
	}
	return (SH_SUCCESS);
}
