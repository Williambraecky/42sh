/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnonprint_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:03:44 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/23 15:16:41 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*g_nonprint_char = "\t\v\n\r\f\e\a\b";

static char	*g_nonprint_str[] =
{
	['\t'] = "\\t",
	['\v'] = "\\v",
	['\n'] = "\\n",
	['\r'] = "\\r",
	['\f'] = "\\f",
	['\e'] = "\\e",
	['\a'] = "\\a",
	['\b'] = "\\b"
};

void		ft_putnonprint_fd(char *str, int fd)
{
	size_t	len;

	while (*str)
	{
		len = ft_strcspn(str, g_nonprint_char);
		write(fd, str, len);
		str += len;
		if (*str)
		{
			write(fd, g_nonprint_str[(int)*str],
				ft_strlen(g_nonprint_str[(int)*str]));
			str++;
		}
	}
}
