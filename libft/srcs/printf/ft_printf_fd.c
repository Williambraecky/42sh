/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 14:18:08 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 15:54:57 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_fd(int fd, const char *format, ...)
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
	ft_putnstr_fd(flags->str, flags->printed, fd);
	printed = flags->printed;
	free(flags->str);
	free(flags);
	return (printed);
}
