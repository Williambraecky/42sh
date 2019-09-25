/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 09:38:12 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 12:28:46 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_handle_intlong(va_list *list, t_flags *flags)
{
	flags->longnb++;
	ft_printf_handle_int(list, flags);
}

void	ft_printf_handle_int(va_list *list, t_flags *flags)
{
	intmax_t	n;
	char		*itoa;

	n = ft_signed_int(list, flags);
	itoa = ft_printf_itoa(n, 10, flags);
	ft_printf_handle_string_intern(itoa, flags);
	free(itoa);
}
