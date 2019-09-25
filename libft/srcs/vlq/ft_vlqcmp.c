/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:59:21 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/17 16:05:00 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_vlqcmp(t_vlq a, t_vlq b)
{
	size_t	a_len;
	size_t	b_len;
	size_t	i;

	a_len = ft_vlqlen(a);
	b_len = ft_vlqlen(b);
	if (a_len < b_len)
		return (-1);
	else if (a_len > b_len)
		return (1);
	while (a_len)
	{
		a_len--;
		b_len--;
		i = 63;
		while (i--)
		{
			if (a[a_len] & (1l << i) && !(b[b_len] & (1l << i)))
				return (1);
			else if (!(a[a_len] & (1l << i) && b[b_len] & (1l << i)))
				return (-1);
		}
	}
	return (0);
}
