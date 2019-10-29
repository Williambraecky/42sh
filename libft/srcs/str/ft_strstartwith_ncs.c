/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstartwith_ncs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:59:06 by ntom              #+#    #+#             */
/*   Updated: 2019/10/29 16:07:58 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ncs = not case sensitive
*/

int		ft_strstartswith_ncs(const char *str, const char *find)
{
	while (ft_tolower(*str) == ft_tolower(*find) && *str)
	{
		str++;
		find++;
	}
	if (*find == '\0')
		return (1);
	return (0);
}
