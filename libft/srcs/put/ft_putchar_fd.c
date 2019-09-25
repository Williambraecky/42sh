/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:38:09 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/07/03 11:25:59 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int		ft_get_and_shift(int *i)
{
	int tmp;

	tmp = *i;
	*i = *i >> 6;
	return (tmp);
}

static void		ft_default_unicode(char *buffer)
{
	buffer[2] = 0xEF;
	buffer[1] = 0xBF;
	buffer[0] = 0xBD;
}

/*
** L'elem 0 definit le nombres de bytes utilises par le char unicode
** et contient egalement les x premiers bits du charactere,
** 11XXXXX = 2 bytes, 111XXXX = 3 bytes, 1111XXXX = 4 bytes
** ^ 0xC0             ^ 0xE0             ^ 0xF0
** tout les bytes en plus commencent par 10 (0x80)
** Un charactere n'utilises jamais tout les bits
*/

static void		ft_putunicode(int c, int fd)
{
	char	buffer[5];

	ft_memset(buffer, 0, 5);
	if (c <= 0x7FF)
	{
		buffer[1] = 0x80 | (ft_get_and_shift(&c) & 0x3F);
		buffer[0] = 0xC0 | (c & 0x1F);
	}
	else if (c <= 0x7FFF)
	{
		buffer[2] = 0x80 | (ft_get_and_shift(&c) & 0x3F);
		buffer[1] = 0x80 | (ft_get_and_shift(&c) & 0x3F);
		buffer[0] = 0xE0 | (c & 0x7);
	}
	else if (c <= 0x7FFFF)
	{
		buffer[3] = 0x80 | (ft_get_and_shift(&c) & 0x3F);
		buffer[2] = 0x80 | (ft_get_and_shift(&c) & 0x3F);
		buffer[1] = 0x80 | (ft_get_and_shift(&c) & 0x3F);
		buffer[0] = 0xF0 | (c & 0x7);
	}
	else
		ft_default_unicode(buffer);
	ft_putstr_fd(buffer, fd);
}

void			ft_putchar_fd(int c, int fd)
{
	if (c <= 0x7F)
		write(fd, &c, 1);
	else
		ft_putunicode(c, fd);
}
