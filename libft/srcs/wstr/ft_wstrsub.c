/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrsub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:32:38 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/11 16:36:19 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_wstrsub(char *str, size_t start, size_t len)
{
	size_t	end;
	size_t	len_str;

	len_str = ft_wstrlen(str);
	if (start > len_str)
		return (NULL);
	end = start + len;
	if (end > len_str)
		end = len_str;
	return (ft_strsub(str, ft_wstrindex(str, start) - str,
			ft_wstrindex(str, end) - str));
}
