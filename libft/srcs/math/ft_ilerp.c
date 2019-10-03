/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ilerp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 11:32:25 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/15 15:10:58 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_ilerp(double start, double end, double target)
{
	if (target == start)
		return (0.00);
	else if (target == end)
		return (1.00);
	return ((target - start) / (end - start));
}
