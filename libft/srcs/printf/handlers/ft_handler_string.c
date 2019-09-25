/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 09:41:52 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 12:34:38 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_handle_string_intern(char *str, t_flags *flags)
{
	size_t	len;

	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	flags->width -= (int)len;
	if (!(flags->flags & MINUS) && flags->width > 0)
		ft_printf_putnchar(flags->flags & ZERO &&
				(!(flags->flags & PRECISION)) ?
				'0' : ' ', flags, (size_t)flags->width);
	ft_printf_putnstr(str, len, flags);
	if (flags->flags & MINUS && flags->width > 0)
		ft_printf_putnchar(' ', flags, (size_t)flags->width);
}

size_t	ft_wcharstrlen(wchar_t *str, t_flags *flags)
{
	size_t len;
	size_t max;

	len = 0;
	max = LIB_LONG_MAX;
	if (flags->flags & PRECISION && flags->precision >= 0)
		max = (size_t)flags->precision;
	while (*str)
	{
		if (len + ft_wintt_len(*str) > max)
			break ;
		len += ft_wintt_len(*str++);
	}
	return (len);
}

void	ft_printf_handle_stringlong(va_list *list, t_flags *flags)
{
	wchar_t	*str;
	size_t	len;
	size_t	written;

	str = (wchar_t *)ft_arg_for(list, flags);
	if (str == NULL)
		str = L"(null)";
	len = ft_wcharstrlen(str, flags);
	if (flags->flags & PRECISION && flags->precision < (int)len
			&& flags->precision >= 0)
		len = flags->precision;
	flags->width -= (int)len;
	if (!(flags->flags & MINUS) && flags->width > 0)
		ft_printf_putnchar(flags->flags & ZERO &&
				(!(flags->flags & PRECISION) || flags->precision >= 0) ?
				'0' : ' ', flags, (size_t)flags->width);
	written = 0;
	while (*str && written < len)
	{
		written += ft_wintt_len(*str);
		if (written <= len)
			ft_handle_wint_t(*str++, flags);
	}
	if (flags->flags & MINUS && flags->width > 0)
		ft_printf_putnchar(' ', flags, (size_t)flags->width);
}

void	ft_printf_handle_string(va_list *list, t_flags *flags)
{
	char	*str;

	if (flags->longnb > 0)
	{
		ft_printf_handle_stringlong(list, flags);
		return ;
	}
	str = ft_arg_for(list, flags);
	if (str == NULL)
		str = "(null)";
	if (flags->flags & PRECISION && flags->precision >= 0 &&
			(int)ft_strlen(str) > flags->precision)
	{
		str = ft_strncpy(ft_strnew(flags->precision), str, flags->precision);
		flags->flags ^= PRECISION;
		ft_printf_handle_string_intern(str, flags);
		free(str);
	}
	else
		ft_printf_handle_string_intern(str, flags);
}
