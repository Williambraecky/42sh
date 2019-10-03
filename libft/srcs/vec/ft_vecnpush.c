/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecnpush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:02:15 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/06/17 19:03:56 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vec.h"
#include <stdarg.h>

int		ft_vecnpush(t_vec *vec, size_t n, ...)
{
	va_list	list;
	void	*next;

	va_start(list, n);
	while (n--)
	{
		next = va_arg(list, void*);
		if (ft_vecpush(vec, next))
			return (1);
	}
	va_end(list);
	return (0);
}
