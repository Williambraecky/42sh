/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 09:43:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 18:26:53 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Slightly different from ft_putunicode but see ft_putunicode for information
*/

void	ft_handle_wint_t(wint_t c, t_flags *flags)
{
	if (c < 0x7F)
		ft_printf_putchar((char)c, flags);
	else if (c < 0x7FF)
	{
		ft_printf_putchar((char)(c >> 6 | 0xC0), flags);
		ft_printf_putchar((char)((c & 0x3F) | 0x80), flags);
	}
	else if (c < 0xFFFF)
	{
		ft_printf_putchar((char)(c >> 12 | 0xE0), flags);
		ft_printf_putchar((char)(((c >> 6) & 0x3F) | 0x80), flags);
		ft_printf_putchar((char)((c & 0x3F) | 0x80), flags);
	}
	else if (c < 0x10FFFF)
	{
		ft_printf_putchar((char)(c >> 18 | 0xF0), flags);
		ft_printf_putchar((char)(((c >> 12) & 0x3F) | 0x80), flags);
		ft_printf_putchar((char)(((c >> 6) & 0x3F) | 0x80), flags);
		ft_printf_putchar((char)((c & 0x3F) | 0x80), flags);
	}
}

size_t	ft_wintt_len(wint_t c)
{
	if (c < 0x7F)
		return (1);
	else if (c < 0x7FF)
		return (2);
	else if (c < 0xFFFF)
		return (3);
	else if (c < 0x10FFFF)
		return (4);
	return (0);
}

void	ft_printf_handle_charlong(va_list *list, t_flags *flags)
{
	wint_t c;

	c = (wint_t)ft_arg_for(list, flags);
	flags->width -= ft_wintt_len(c);
	if (!(flags->flags & MINUS) && flags->width > 0)
		ft_printf_putnchar(flags->flags & ZERO ? '0' : ' ', flags,
				(size_t)flags->width);
	ft_handle_wint_t(c, flags);
	if (flags->flags & MINUS && flags->width > 0)
		ft_printf_putnchar(' ', flags, (size_t)flags->width);
}

void	ft_printf_handle_char(va_list *list, t_flags *flags)
{
	int c;

	if (flags->longnb > 0)
	{
		ft_printf_handle_charlong(list, flags);
		return ;
	}
	c = (char)ft_arg_for(list, flags);
	ft_printf_handle_none(c, flags);
}
