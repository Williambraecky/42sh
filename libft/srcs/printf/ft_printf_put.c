/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 17:54:02 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 15:58:39 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		g_buffer[PRINTF_BUFFER];
static int		g_index = 0;

void	ft_printf_putchar(int c, t_flags *flags)
{
	flags->printed++;
	g_buffer[g_index++] = c;
	if (g_index == PRINTF_BUFFER)
		ft_printf_flush(flags);
}

void	ft_printf_putnchar(int c, t_flags *flags, size_t amount)
{
	while (amount--)
		ft_printf_putchar(c, flags);
}

void	ft_printf_putnstr(const char *str, size_t len, t_flags *flags)
{
	while (len--)
		ft_printf_putchar(*str++, flags);
}

void	ft_printf_putstr(const char *str, t_flags *flags)
{
	ft_printf_putnstr(str, ft_strlen(str), flags);
}

void	ft_printf_flush(t_flags *flags)
{
	char *tmp;

	if (g_index == 0)
		return ;
	if (flags->str == NULL)
		flags->str = malloc(sizeof(char) * flags->printed);
	else
	{
		tmp = flags->str;
		flags->str = malloc(sizeof(char) * flags->printed);
		if (flags->str)
			ft_memcpy(flags->str, tmp, flags->printed - g_index);
		free(tmp);
	}
	if (!flags->str)
	{
		flags->printed = -1;
		return ;
	}
	ft_memcpy(flags->str + flags->printed - g_index, g_buffer, g_index);
	g_index = 0;
}
