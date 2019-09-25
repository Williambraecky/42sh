/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 16:32:37 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 12:19:44 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_handler		g_handlers[] =
{
	{'c', &ft_printf_handle_char},
	{'C', &ft_printf_handle_charlong},
	{'d', &ft_printf_handle_int},
	{'D', &ft_printf_handle_intlong},
	{'i', &ft_printf_handle_int},
	{'s', &ft_printf_handle_string},
	{'S', &ft_printf_handle_stringlong},
	{'p', &ft_printf_handle_pointer},
	{'n', &ft_printf_handle_printed},
	{'o', &ft_printf_handle_octal},
	{'O', &ft_printf_handle_octallong},
	{'x', &ft_printf_handle_hexa_low},
	{'X', &ft_printf_handle_hexa_high},
	{'u', &ft_printf_handle_unsigned},
	{'U', &ft_printf_handle_unsignedlong},
	{'f', &ft_printf_handle_float},
	{'F', &ft_printf_handle_float},
	{'\0', NULL}
};

void		*ft_arg_for(va_list *list, t_flags *flags)
{
	va_list	copy;
	void	*p;

	if (flags->arg_pos != 0)
	{
		va_copy(copy, list[1]);
		p = ft_arg_at(copy, flags->arg_pos);
		va_end(copy);
	}
	else
		p = va_arg(list[0], void *);
	return (p);
}

void		ft_handle(char **str, va_list *list, t_flags *flags)
{
	size_t	i;

	i = 0;
	while (g_handlers[i].c)
	{
		if (g_handlers[i].c == **str && (*str)++)
		{
			g_handlers[i].handler(list, flags);
			return ;
		}
		i++;
	}
	if (**str)
		ft_printf_handle_none(*(*str)++, flags);
}

intmax_t	ft_signed_int(va_list *list, t_flags *flag)
{
	intmax_t	n;

	n = (intmax_t)ft_arg_for(list, flag);
	if (flag->longnb >= 2 || flag->flags & LENGTH_J || flag->flags & LENGTH_Z)
		n = (intmax_t)n;
	else if (flag->longnb == 1)
		n = (intmax_t)((long int)n);
	else if (flag->shortnb >= 2)
		n = (intmax_t)((char)n);
	else if (flag->shortnb == 1)
		n = (intmax_t)((short int)n);
	else
		n = (intmax_t)(int)n;
	return (n);
}

uintmax_t	ft_unsigned_int(va_list *list, t_flags *flag)
{
	uintmax_t	n;

	n = (uintmax_t)ft_arg_for(list, flag);
	if (flag->longnb >= 2 || flag->flags & LENGTH_J || flag->flags & LENGTH_Z)
		n = (uintmax_t)n;
	else if (flag->longnb == 1)
		n = (uintmax_t)((unsigned long int)n);
	else if (flag->shortnb >= 2)
		n = (uintmax_t)((unsigned char)n);
	else if (flag->shortnb == 1)
		n = (uintmax_t)((unsigned short int)n);
	else
		n = (uintmax_t)(unsigned int)n;
	return (n);
}
