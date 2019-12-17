/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_alias.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:30:12 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/16 14:31:08 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		has_alias(t_sh *shell, char *alias)
{
	return (ft_mapcontains(shell->aliases, alias));
}
