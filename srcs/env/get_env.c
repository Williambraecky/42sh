/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:13:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 22:00:19 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_env(t_sh *shell, char *key, char **result)
{
	t_var	*var;

	if (!shell->vars || !(var = ft_mapget(shell->vars, key)) ||
		var->exported == 0)
		return (SH_ERR_NOEXIST);
	if (!(*result = ft_strdup(var->var)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
