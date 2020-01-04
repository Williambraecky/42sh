/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_nocolor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:26:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/16 16:29:55 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static size_t	skip_color_code(char *str, size_t pos)
{
	size_t len;

	len = pos + 1;
	if (str[len++] != '[')
		return (1);
	while (ft_isdigit(str[len]))
		len++;
	if (str[len++] != 'm')
		return (1);
	return (len - pos);
}

size_t			strlen_nocolor(char *str)
{
	size_t i;
	size_t len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == 0x1B)
			i += skip_color_code(str, i);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
