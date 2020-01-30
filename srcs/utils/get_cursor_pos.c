/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cursor_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:44:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/30 23:00:39 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE:
**	ERROR CODES:
**	- 0: success
**	- 1: invalid terminal
**	- 2: read error
*/

static void	reinsert_in_buffer(char *buffer, char *end)
{
	char	buff;
	int		queued;

	if (ioctl(0, FIONREAD, &queued) == -1)
		return ;
	while (*buffer != '\e')
		ioctl(0, TIOCSTI, buffer++);
	while (*end)
		ioctl(0, TIOCSTI, end++);
	while (queued--)
	{
		read(0, &buff, 1);
		ioctl(0, TIOCSTI, &buff);
	}
}

static int	read_pos_from_buffer(char *buffer, int *x, int *y)
{
	char	*tmp;
	int		tmp_y;

	if (!(tmp = ft_strchr(buffer, '[')))
		return (2);
	tmp_y = ft_atoi(tmp + 1);
	if (!(tmp = ft_strchr(tmp, ';')))
		return (2);
	*x = ft_atoi(tmp + 1);
	tmp += ft_intlen(*x) + 2;
	*y = tmp_y;
	reinsert_in_buffer(buffer, tmp);
	return (0);
}

int			get_cursor_pos(t_sh *sh, int *x, int *y)
{
	char	buf[256];
	int		ret;
	size_t	i;

	if (sh->interactive_mode == 0)
		return (1);
	ft_memset(buf, 0, 256);
	write(0, "\033[6n", 4);
	i = 0;
	while (i == 0 || (buf[i - 1] != 'R' && i < 255))
	{
		if (!(ret = read(0, buf + i, 1)))
			return (2);
		i++;
	}
	if (i < 2 || read_pos_from_buffer(buf, x, y) || i == 256)
		return (2);
	return (0);
}
