/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 21:38:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 21:49:58 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			get_var(t_sh *shell, char *key, char **result)
{
	t_var	*var;

	if (!shell->vars || !(var = ft_mapget(shell->vars, key)))
		return (SH_ERR_NOEXIST);
	*result = var->var;
	return (SH_SUCCESS);
}
