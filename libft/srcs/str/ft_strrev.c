/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 11:51:09 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/08/14 11:17:42 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(char *str)
{
	char	*start;
	char	*end;

	start = str;
	end = str + ft_strlen(str) - 1;
	while (start < end)
		ft_swapchar(start++, end--);
	return (str);
}
