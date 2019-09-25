/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_hexa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 18:37:54 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 12:28:07 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_handle_hexa_low(va_list *list, t_flags *flags)
{
	uintmax_t	n;
	char		*itoa;

	n = ft_unsigned_int(list, flags);
	itoa = ft_printf_uitoa(n, 16, flags);
	itoa = ft_strtolower(itoa);
	ft_printf_handle_string_intern(itoa, flags);
	free(itoa);
}

void	ft_printf_handle_hexa_high(va_list *list, t_flags *flags)
{
	uintmax_t	n;
	char		*itoa;

	n = ft_unsigned_int(list, flags);
	itoa = ft_printf_uitoa(n, 16, flags);
	ft_printf_handle_string_intern(itoa, flags);
	free(itoa);
}
