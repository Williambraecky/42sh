/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_octal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 17:37:08 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 18:13:25 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_handle_octallong(va_list *list, t_flags *flags)
{
	flags->longnb++;
	ft_printf_handle_octal(list, flags);
}

void	ft_printf_handle_octal(va_list *list, t_flags *flags)
{
	uintmax_t	n;
	char		*itoa;

	n = ft_unsigned_int(list, flags);
	if (flags->flags & HASHTAG && flags->precision > 0 && n != 0)
		flags->precision--;
	itoa = ft_printf_uitoa(n, 8, flags);
	ft_printf_handle_string_intern(itoa, flags);
	free(itoa);
}
