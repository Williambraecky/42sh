/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 16:05:02 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/17 15:33:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*g_colors[][2] =
{
	{"eoc", "\e[0m"},
	{"bold", "\e[1m"},
	{"dim", "\e[2m"},
	{"underline", "\e[4m"},
	{"blink", "\e[5m"},
	{"invert", "\e[7m"},
	{"hidden", "\e[8m"},
	{"def", "\e[39m"},
	{"black", "\e[30m"},
	{"red", "\e[31m"},
	{"green", "\e[32m"},
	{"yellow", "\e[33m"},
	{"blue", "\e[34m"},
	{"magenta", "\e[35m"},
	{"cyan", "\e[36m"},
	{"gray", "\e[37m"},
	{"dark_gray", "\e[90m"},
	{"light_red", "\e[91m"},
	{"light_green", "\e[92m"},
	{"light_yellow", "\e[93m"},
	{"light_blue", "\e[94m"},
	{"light_magenta", "\e[95m"},
	{"light_cyan", "\e[96m"},
	{"white", "\e[97m"},
	{"bg_def", "\e[49m"},
	{"bg_black", "\e[40m"},
	{"bg_red", "\e[41m"},
	{"bg_green", "\e[42m"},
	{"bg_yellow", "\e[43m"},
	{"bg_blue", "\e[44m"},
	{"bg_magenta", "\e[45m"},
	{"bg_cyan", "\e[46m"},
	{"bg_gray", "\e[47m"},
	{"bg_dark_gray", "\e[100m"},
	{"bg_light_red", "\e[101m"},
	{"bg_light_green", "\e[102m"},
	{"bg_light_yellow", "\e[103m"},
	{"bg_light_blue", "\e[104m"},
	{"bg_light_magenta", "\e[105m"},
	{"bg_light_cyan", "\e[106m"},
	{"bg_white", "\e[107m"},
	{NULL, NULL}
};

void	ft_handle_colors(char **str, t_flags *flags)
{
	char	*tmp;
	size_t	i;

	tmp = (*str) + 1;
	i = 0;
	while (g_colors[i][0])
	{
		if (ft_strstartswith(tmp, g_colors[i][0]))
		{
			if (*(tmp + ft_strlen(g_colors[i][0])) != '}')
				break ;
			ft_printf_putstr(g_colors[i][1], flags);
			tmp += ft_strlen(g_colors[i][0]) + 1;
			*str = tmp;
			return ;
		}
		i++;
	}
	ft_printf_putchar('{', flags);
	(*str)++;
}
