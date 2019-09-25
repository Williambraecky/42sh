/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_none.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 10:03:33 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 12:29:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_handle_none(int c, t_flags *flags)
{
	flags->width -= 1;
	if (!(flags->flags & MINUS) && flags->width > 0)
		ft_printf_putnchar(flags->flags & ZERO ? '0' : ' ', flags,
				(size_t)flags->width);
	ft_printf_putchar(c, flags);
	if (flags->flags & MINUS && flags->width > 0)
		ft_printf_putnchar(' ', flags, (size_t)flags->width);
}
