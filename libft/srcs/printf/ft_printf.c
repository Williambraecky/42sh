/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 16:37:01 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 15:58:23 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags	*ft_new_flags(void)
{
	t_flags *flags;

	if (!(flags = ft_memalloc(sizeof(t_flags))))
		return (NULL);
	flags->width = UNDEFINED_WIDTH;
	return (flags);
}

int		ft_printf(const char *format, ...)
{
	va_list		list[2];
	t_flags		*flags;
	int			printed;

	if (format == NULL || !(flags = ft_new_flags()))
		return (-1);
	va_start(list[0], format);
	va_copy(list[1], list[0]);
	ft_parse_printf((char *)format, list, flags);
	ft_printf_flush(flags);
	va_end(list[0]);
	va_end(list[1]);
	ft_putnstr(flags->str, flags->printed);
	printed = flags->printed;
	free(flags->str);
	free(flags);
	return (printed);
}
