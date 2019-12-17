/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_alias.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:23:06 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 17:24:05 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** Basic alias -> t_vec *token conversion
*/

t_alias	*get_alias(t_sh *shell, char *alias)
{
	return ((t_alias*)ft_mapget(shell->aliases, alias));
}
