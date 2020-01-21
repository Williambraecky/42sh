/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:39:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 22:40:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	reset_hash(t_sh *shell, char *cmd)
{
	t_hashed	*hashed;

	if (get_hash(shell, cmd, &hashed) != SH_SUCCESS)
		return ;
	hashed->uses = 0;
}
