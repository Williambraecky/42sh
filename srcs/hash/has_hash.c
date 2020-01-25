/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:29:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/25 23:10:06 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		has_hash(t_sh *shell, char *bin)
{
	if (!shell->use_hash)
		return (0);
	return (ft_mapcontains(shell->use_hash, bin));
}
