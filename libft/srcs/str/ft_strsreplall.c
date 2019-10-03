/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsreplall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:51:10 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/05 12:11:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_occur(char *str, char *match)
{
	size_t	occur;

	occur = 0;
	while ((str = ft_strstr(str, match)))
	{
		occur++;
		str += 1;
	}
	return (occur);
}

char			*ft_strsreplall(char *str, char *match, char *replacement)
{
	char	*ret;
	char	*tmp;
	size_t	occur;
	size_t	tot_len;

	if (ft_strlen(match) == 0 || (occur = ft_count_occur(str, match)) == 0)
		return (ft_strdup(str));
	tot_len = ft_strlen(str) - (occur * ft_strlen(match));
	tot_len += occur * ft_strlen(replacement);
	if (!(ret = ft_strnew(tot_len)))
		return (NULL);
	tmp = str;
	while ((tmp = ft_strstr(tmp, match)))
	{
		ft_strncat(ret, str, tmp - str);
		ft_strcat(ret, replacement);
		tmp += ft_strlen(match);
		str = tmp;
	}
	ft_strcat(ret, str);
	return (ret);
}
