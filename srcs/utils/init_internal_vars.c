/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_internal_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:39:11 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 23:04:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	*g_base_vars[][2] =
{
	{"?", "0"},
	{"PS1", "${light_green}\\u@\\h${eoc}:${magenta}\\W ${blue}\\g${eoc}$ "},
	{"IFS", "\n\t "},
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
	{"FCEDIT", "/usr/bin/vim"},
	{NULL, NULL},
};

int		init_internal_vars(t_sh *shell)
{
	char	*tmp;
	size_t	i;
	int		ret;

	ret = 0;
	if (!(tmp = ft_itoa(getpid())))
		return (1);
	ret += add_var(shell, "$", tmp);
	free(tmp);
	i = 0;
	while (g_base_vars[i][0] != NULL && ret == 0)
	{
		ret += add_var(shell, g_base_vars[i][0], g_base_vars[i][1]);
		i++;
	}
	return (ret);
}
