/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstartswith.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 16:43:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/09 16:44:56 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strstartswith(const char *str, const char *find)
{
	while (*str == *find && *str)
	{
		str++;
		find++;
	}
	if (*find == '\0')
		return (1);
	return (0);
}
