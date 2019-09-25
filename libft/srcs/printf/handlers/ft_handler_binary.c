/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_binary.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 13:31:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 12:23:15 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_handle_binary(va_list *list, t_flags *flags)
{
	uintmax_t	n;
	char		*itoa;

	n = ft_unsigned_int(list, flags);
	itoa = ft_printf_uitoa(n, 2, flags);
	ft_printf_handle_string_intern(itoa, flags);
	free(itoa);
}
