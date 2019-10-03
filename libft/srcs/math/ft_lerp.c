/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lerp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 11:25:49 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/15 15:11:04 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_lerp(double start, double end, double percent)
{
	if (percent == 0.00)
		return (start);
	else if (percent == 1.00)
		return (end);
	return (start + (end - start) * percent);
}
