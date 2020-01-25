/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_add_use.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 22:17:52 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/25 23:10:26 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		hash_add_use_insert(t_sh *shell, char *name, char *path)
{
	if (!shell->use_hash || !shell->allow_hash_update)
		return (SH_SUCCESS);
	if (!has_hash(shell, name))
	{
		if (add_hash(shell, name, path) != SH_SUCCESS)
			return (SH_ERR_MALLOC);
	}
	hash_add_use(shell, name);
	return (SH_SUCCESS);
}

void	hash_add_use(t_sh *shell, char *name)
{
	t_hashed	*hashed;

	if (!shell->use_hash || !shell->allow_hash_update)
		return ;
	if (get_hash(shell, name, &hashed) != SH_SUCCESS)
		return ;
	hashed->uses += 1;
}
