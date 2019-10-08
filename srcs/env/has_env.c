/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:16:28 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/08 17:17:03 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		has_env(t_sh *shell, char *key)
{
	if (!shell->env)
		return (0);
	return (ft_mapcontains(shell->env, key));
}
