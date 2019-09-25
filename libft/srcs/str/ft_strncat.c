/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 08:50:06 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/17 10:05:23 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	slen_1;

	slen_1 = ft_strlen(s1);
	while (n-- && *s2)
		s1[slen_1++] = *s2++;
	s1[slen_1] = '\0';
	return (s1);
}
