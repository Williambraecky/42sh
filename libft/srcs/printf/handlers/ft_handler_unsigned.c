/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_unsigned.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 09:52:48 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 12:35:18 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_handle_unsignedlong(va_list *list, t_flags *flags)
{
	flags->longnb++;
	ft_printf_handle_unsigned(list, flags);
}

void	ft_printf_handle_unsigned(va_list *list, t_flags *flags)
{
	uintmax_t	n;
	char		*itoa;

	n = ft_unsigned_int(list, flags);
	itoa = ft_printf_uitoa(n, 10, flags);
	ft_printf_handle_string_intern(itoa, flags);
	free(itoa);
}
