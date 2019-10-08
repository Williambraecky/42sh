/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:13:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/08 17:19:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_env(t_sh *shell, char *key, char **result)
{
	if (!shell->env)
		return (SH_ERR_NOEXIST);
	if (!(*result = ft_mapget(shell->env, key)))
		return (SH_ERR_ENV_NOEXIST);
	return (SH_SUCCESS);
}
