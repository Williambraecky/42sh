/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 15:31:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/15 15:33:10 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	*ft_arg_at(va_list list, size_t pos)
{
	void	*p;

	if (pos == 0)
		return (NULL);
	while (pos--)
		p = va_arg(list, void *);
	return (p);
}
