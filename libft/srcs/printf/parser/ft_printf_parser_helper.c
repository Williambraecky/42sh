/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 11:46:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 13:00:05 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_read_star_flag(char **str, va_list *list)
{
	char	*tmp;
	int		arg_pos;
	int		ret;
	va_list	copy;

	arg_pos = 0;
	tmp = *str;
	if (ft_strchr(tmp, '$') != NULL)
	{
		while (*tmp != '$')
		{
			if (!ft_isdigit(*tmp))
				return (va_arg(list[0], int));
			arg_pos = arg_pos * 10 + (*tmp++ - '0');
		}
		*str = tmp + 1;
		va_copy(copy, list[1]);
		ret = (int)ft_arg_at(copy, arg_pos);
		va_end(copy);
		return (ret);
	}
	return (va_arg(list[0], int));
}

t_flags	*ft_reset_flags(t_flags *flags)
{
	flags->flags = 0;
	flags->width = UNDEFINED_WIDTH;
	flags->precision = 0;
	flags->longnb = 0;
	flags->shortnb = 0;
	flags->arg_pos = 0;
	return (flags);
}
