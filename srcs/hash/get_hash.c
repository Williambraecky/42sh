/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:28:15 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/19 15:30:41 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_hash(t_sh *shell, char *bin, t_hashed **hash)
{
	if (has_hash(shell, bin))
		return (SH_ERR_NOEXIST);
	*hash = ft_mapget(shell->use_hash, bin);
	return (SH_SUCCESS);
}
