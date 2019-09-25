/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 17:53:14 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 18:21:15 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_getprefix(uintmax_t value, size_t base, t_flags *flag)
{
	if (!(flag->flags & HASHTAG) || value == 0)
		return ("");
	else if (base == 16)
		return ("0X");
	else if (base == 8)
		return ("0");
	return ("");
}

char	*ft_printf_uitoa(uintmax_t value, size_t base, t_flags *flag)
{
	char	*str;
	char	*prefix;
	size_t	prefixlen;
	size_t	len;

	if (flag->flags & PRECISION && value == 0 && flag->precision == 0)
	{
		return (flag->flags & HASHTAG && base == 8 ? ft_strdup("0") :
			ft_strdup(""));
	}
	prefix = ft_printf_getprefix(value, base, flag);
	prefixlen = ft_strlen(prefix);
	len = ft_max(flag->precision, ft_uintlen_base(value, base)) + prefixlen;
	if (flag->flags & ZERO && ((flag->width) >= (int)len)
			&& !(flag->flags & MINUS) && !(flag->flags & PRECISION))
		len = (size_t)flag->width;
	if (!(str = ft_strnew(len)))
		return (NULL);
	ft_strcpy(str, prefix);
	while (len-- > prefixlen)
	{
		str[len] = ft_itoc_base(value % base, base);
		value /= base;
	}
	return (str);
}

size_t	ft_calclen(intmax_t value, size_t base, t_flags *flag, size_t hassign)
{
	size_t	len;

	if (flag->flags & PRECISION && flag->precision == 0 && value == 0)
		return (0);
	len = ft_max(flag->precision, ft_intlen_base(value, base));
	if (flag->width > 0 && flag->flags & ZERO && !(flag->flags & MINUS) &&
			(!(flag->flags & PRECISION) || flag->precision < 0))
		len = ft_max(len, flag->width - hassign);
	return (len);
}

char	*ft_printf_itoa(intmax_t value, size_t base, t_flags *flag)
{
	char	*str;
	size_t	hassign;
	size_t	neg;
	size_t	len;

	neg = value < 0;
	hassign = neg || flag->flags & BLANK || flag->flags & PLUS;
	len = ft_calclen(value, base, flag, hassign) + hassign;
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (len-- > hassign)
	{
		str[len] = ft_itoc_base(ft_abs(value % (ssize_t)base), base);
		value /= (ssize_t)base;
	}
	if (neg)
		str[0] = '-';
	else if (flag->flags & PLUS)
		str[0] = '+';
	else if (flag->flags & BLANK)
		str[0] = ' ';
	return (str);
}
