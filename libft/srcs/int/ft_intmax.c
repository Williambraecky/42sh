/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 22:15:25 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/10 22:22:59 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int		ft_intmax(int len, ...)
{
	int		max;
	va_list	list;

	if (len == 0)
		return (0);
	va_start(list, len);
	max = va_arg(list, int);
	while (len-- - 1)
		max = ft_max(max, va_arg(list, int));
	va_end(list);
	return (max);
}
