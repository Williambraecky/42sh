/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:09:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/05/29 17:12:45 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	ft_strndel(size_t n, ...)
{
	va_list	list;

	va_start(list, n);
	while (n--)
		ft_strdel(va_arg(list, char **));
	va_end(list);
}
