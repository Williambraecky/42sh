/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_internal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:16:28 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/19 15:24:57 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		has_internal(t_sh *shell, char *key)
{
	if (!shell->internals)
		return (0);
	return (ft_mapcontains(shell->internals, key));
}
