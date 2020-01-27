/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:16:28 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 22:01:00 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		has_env(t_sh *shell, char *key)
{
	t_var	*var;

	if (!shell->vars || !(var = ft_mapget(shell->vars, key)))
		return (0);
	return (var->exported == 1);
}
