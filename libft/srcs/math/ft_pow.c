/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:39:49 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 11:01:23 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_pow(double n, int pow)
{
	double res;

	res = (double)n;
	if (pow == 0)
		return (1.0);
	else if (pow > 0)
	{
		while (pow-- > 1)
			res *= (double)n;
		return (res);
	}
	else
	{
		res = 1.0;
		while (pow++)
			res /= (double)n;
		return (res);
	}
}
