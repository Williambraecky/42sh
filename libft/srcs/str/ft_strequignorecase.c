/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequignorecase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 11:47:43 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/06 11:49:16 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequignorecase(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			break ;
		s1++;
		s2++;
	}
	return (!*s1 && !*s2);
}
