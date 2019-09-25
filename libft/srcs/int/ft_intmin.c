/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 22:10:44 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/10 22:22:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int		ft_intmin(int len, ...)
{
	int		min;
	va_list	list;

	if (len == 0)
		return (0);
	va_start(list, len);
	min = va_arg(list, int);
	while (len-- - 1)
		min = ft_min(min, va_arg(list, int));
	va_end(list);
	return (min);
}
