/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ilerp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 11:32:25 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/12 11:33:11 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_ilerp(float start, float end, float target)
{
	if (target == start)
		return (0.00);
	else if (target == end)
		return (1.00);
	return ((target - start) / (end - start));
}
