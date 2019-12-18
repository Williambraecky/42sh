/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_alias.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:23:06 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/18 14:15:57 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** Basic alias -> t_vec *token conversion
*/

char	*get_alias(t_sh *shell, char *alias)
{
	return ((char*)ft_mapget(shell->aliases, alias));
}
