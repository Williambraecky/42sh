/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_clone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 21:34:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 21:39:09 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_var_clone(t_sh *shell, char *key, char **result)
{
	t_var	*var;

	if (!shell->vars || !(var = ft_mapget(shell->vars, key)))
		return (SH_ERR_NOEXIST);
	if (!(*result = ft_strdup(var->var)))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}
