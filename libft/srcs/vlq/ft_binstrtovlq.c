/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binstrtovlq.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:25:52 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/17 17:29:37 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vlq	ft_binstrtovlq(const char *str)
{
	t_vlq	result;
	size_t	len;
	size_t	i;

	len = (ft_strlen(str) / 63) + 1;
	if (!(result = ft_vlqnew(len)))
		return (NULL);
	while (len--)
	{
		i = 63;
		while (i--)
			result[len] |= str[(len * 63) + i] == '1' ? (1l << i) : 0;
	}
	return (result);
}
