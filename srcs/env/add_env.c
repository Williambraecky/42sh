/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:17:23 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 21:57:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: clones the key and the value
*/

int		add_env(t_sh *shell, char *key, char *value)
{
	char	*key_dup;
	t_var	var;

	if (!shell->vars)
		return (SH_ERR_NOEXIST);
	if (!(key_dup = ft_strdup(key)) ||
		!(var.var = ft_strdup(value)))
	{
		free(key_dup);
		return (SH_ERR_MALLOC);
	}
	var.exported = 1;
	if (ft_mapput(shell->vars, key_dup, &var, sizeof(var)) != MAP_OK)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
