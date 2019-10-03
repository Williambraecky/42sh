/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsrepl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:44:03 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/05 11:48:55 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsrepl(char *str, char *match, char *replacement)
{
	char	*ret;
	char	*tmp;
	size_t	total_len;

	if (!(tmp = ft_strstr(str, match)))
		return (ft_strdup(str));
	total_len = tmp - str;
	total_len += ft_strlen(replacement);
	total_len += ft_strlen(tmp + ft_strlen(match));
	if (!(ret = ft_strnew(total_len)))
		return (NULL);
	ft_strncpy(ret, str, tmp - str);
	ft_strcat(ret, replacement);
	ft_strcat(ret, tmp + ft_strlen(match));
	return (ret);
}
