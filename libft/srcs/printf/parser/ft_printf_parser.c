/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:16:33 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 12:40:22 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_paramed_width(char **str, va_list *list, t_flags *flags)
{
	int		i;

	i = 0;
	while (ft_isdigit(**str))
		i = i * 10 + (*(*str)++ - '0');
	flags->width = i != 0 ? i : flags->width;
	if (**str == '*' && (*str)++)
	{
		flags->width = ft_read_star_flag(str, list);
		if (flags->width < 0)
			flags->flags |= MINUS;
		flags->width = ft_abs(flags->width);
	}
	while (**str == '.' && (*str)++)
	{
		i = 0;
		while (ft_isdigit(**str))
			i = i * 10 + (*(*str)++ - '0');
		if (**str == '*' && (*str)++)
			i = ft_read_star_flag(str, list);
		if (i >= 0)
			flags->flags |= PRECISION;
		flags->precision = ft_max(i, 0);
	}
}

void	ft_handle_flag(char **str, va_list *list, t_flags *flags)
{
	ft_handle_paramed_width(str, list, flags);
	if (flags->width < 0)
	{
		flags->width = ft_abs(flags->width);
		flags->flags |= MINUS;
	}
	while (**str && ft_strchr("lhjz", **str) != NULL)
	{
		if (**str == 'l')
			flags->longnb++;
		else if (**str == 'h')
			flags->shortnb++;
		else if (**str == 'j')
			flags->flags |= LENGTH_J;
		else if (**str == 'z')
			flags->flags |= LENGTH_Z;
		(*str)++;
	}
	if (**str && (ft_strchr("0- +#$.*", **str) != NULL || ft_isdigit(**str)))
	{
		ft_parse_flags(str, list, flags);
		return ;
	}
	ft_handle(str, list, flags);
}

void	ft_handle_positional_arg(char **str, t_flags *flags)
{
	char	*tmp;
	size_t	arg_pos;

	tmp = *str;
	arg_pos = 0;
	while (*tmp != '$')
	{
		if (!ft_isdigit(*tmp))
			return ;
		arg_pos = arg_pos * 10 + (*tmp++ - '0');
	}
	*str = tmp;
	flags->arg_pos = arg_pos;
}

void	ft_parse_flags(char **str, va_list *list, t_flags *flags)
{
	if (**str == '%')
		(*str)++;
	while ((**str && ft_strchr("0- +#", **str) != NULL)
			|| (ft_isdigit(**str) && ft_strchr(*str, '$') != NULL))
	{
		if (**str == '0')
			flags->flags |= ZERO;
		else if (**str == '-')
			flags->flags |= MINUS;
		else if (**str == ' ')
			flags->flags |= BLANK;
		else if (**str == '+')
			flags->flags |= PLUS;
		else if (**str == '#')
			flags->flags |= HASHTAG;
		else if (**str == 'L')
			flags->flags |= DOUBLE_L;
		else if (ft_isdigit(**str))
			ft_handle_positional_arg(str, flags);
		(*str)++;
	}
	ft_handle_flag(str, list, flags);
}

void	ft_parse_printf(char *str, va_list *list, t_flags *flags)
{
	char	*tmp;
	char	*tmp2;

	while (*str)
	{
		if (*str == '{')
			ft_handle_colors(&str, flags);
		else if (*str == '%')
			ft_parse_flags(&str, list, ft_reset_flags(flags));
		tmp = ft_strchr(str, '%');
		tmp2 = ft_strchr(str, '{');
		if ((tmp == NULL && tmp2 != NULL) || (tmp && tmp2 && tmp2 < tmp))
			tmp = tmp2;
		if (tmp == NULL)
			break ;
		ft_printf_putnstr(str, tmp - str, flags);
		str = tmp;
	}
	ft_printf_putstr(str, flags);
}
