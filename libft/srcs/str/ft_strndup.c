/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:18:15 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/26 17:19:35 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, size_t n)
{
	char	*new;

	n = ft_min(ft_strlen(str), n);
	if (!(new = ft_strnew(n)))
		return (NULL);
	while (n--)
		new[n] = str[n];
	return (new);
}
