/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 08:43:45 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/17 17:17:11 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	slen_1;

	slen_1 = ft_strlen(s1);
	while (*s2)
		s1[slen_1++] = *s2++;
	s1[slen_1] = '\0';
	return (s1);
}
