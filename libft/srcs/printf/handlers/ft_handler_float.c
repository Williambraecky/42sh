/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 14:33:25 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 15:32:08 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_float_suffix_len(t_flags *flags)
{
	if (flags->precision != 0)
		return ((int)flags->precision + 1);
	if (flags->precision == 0 && flags->flags & HASHTAG)
		return (1);
	return (0);
}

char	*ft_float_int_part(size_t neg, intmax_t i, t_flags *flags)
{
	char		*str;
	size_t		len;
	size_t		hassign;

	hassign = neg || flags->flags & BLANK || flags->flags & PLUS;
	len = ft_intlen_base(i, 10) + neg;
	if (flags->flags & ZERO && !(flags->flags & MINUS))
		len = ft_max(len - (ft_float_suffix_len(flags)), flags->width);
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (len-- > hassign)
	{
		str[len] = ft_abs(i % 10) + '0';
		i /= 10;
	}
	if (neg)
		str[0] = '-';
	else if (flags->flags & PLUS)
		str[0] = '+';
	else if (flags->flags & BLANK)
		str[0] = ' ';
	return (str);
}

double	ft_double_round(double d, t_flags *flags)
{
	if (d >= 0)
		return (d + ft_pow(10, -(flags->precision)) / 2);
	return (d - ft_pow(10, -(flags->precision)) / 2);
}

char	*ft_printf_float_intern(double d, size_t neg, t_flags *flags)
{
	char	*str;
	char	*int_part;
	char	*float_part;
	size_t	len;
	size_t	i;

	d = ft_double_round(d, flags);
	int_part = ft_float_int_part(neg, (intmax_t)d, flags);
	len = ft_float_suffix_len(flags);
	if (!int_part || !(float_part = ft_strnew(len)))
		return (NULL);
	float_part[0] = '.';
	d = d < 0 ? -d : d;
	d = d - (intmax_t)d;
	i = 1;
	while (i < len)
	{
		d *= 10;
		float_part[i++] = ft_abs((char)d) + '0';
		d = d - (char)d;
	}
	str = ft_strjoin(int_part, len == 0 ? "" : float_part);
	free(int_part);
	free(float_part);
	return (str);
}

void	ft_printf_handle_float(va_list *list, t_flags *flags)
{
	double	n;
	va_list	copy;
	size_t	pos;
	char	*str;

	if (flags->flags & DOUBLE_L)
		return ;
	if (flags->arg_pos != 0)
	{
		va_copy(copy, list[1]);
		pos = flags->arg_pos;
		while (pos--)
			n = va_arg(copy, double);
		va_end(copy);
	}
	else
		n = va_arg(list[0], double);
	if (!(flags->flags & PRECISION))
		flags->precision = 6;
	str = ft_printf_float_intern(n, n < 0 || n == -0.0, flags);
	ft_printf_handle_string_intern(str, flags);
	free(str);
}
