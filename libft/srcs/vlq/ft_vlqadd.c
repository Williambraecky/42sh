/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:05:57 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/18 17:52:11 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vlq	ft_vldadd(t_vlq a, t_vlq b)
{
	t_vlq	result;
	size_t	a_len;
	size_t	b_len;
	int		carry;
	size_t	i;

	a_len = ft_vlqlen(a);
	b_len = ft_vlqlen(b);
	if (!(result = ft_vlqnew(sizeof(*result) * (ft_max(a_len, b_len) + 1))))
		return (NULL);
	carry = 0;
	i = 0;
	while (i < a_len || i < b_len || carry)
	{
		result[i] = carry;
		result[i] += i < a_len ? (a[i] & _NOMSB_) : 0;
		result[i] += i < b_len ? (b[i] & _NOMSB_) : 0;
		carry = (result[i] & (1l << 63)) > 0;
		if (i >= a_len - 1 && i >= b_len - 1)
			result[i] &= _NOMSB_;
		else
			result[i] |= (1l << 63);
		i++;
	}
	return (result);
}
