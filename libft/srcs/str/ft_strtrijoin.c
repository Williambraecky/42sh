/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrijoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:24:13 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/29 14:25:39 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrijoin(char *a, char *b, char *c)
{
	char	*ret;

	if (!(ret = ft_strnew(ft_strlen(a) + ft_strlen(b) + ft_strlen(c))))
		return (NULL);
	ft_strcat(ret, a);
	ft_strcat(ret, b);
	ft_strcat(ret, c);
	return (ret);
}
