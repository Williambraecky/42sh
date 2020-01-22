/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cursor_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:44:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/22 23:02:19 by wbraeckm         ###   ########.fr       */
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

static int	read_pos_from_buffer(char *buffer, int *x, int *y)
{
	char	*tmp;
	char	*write;
	int		tmp_y;

	if (!(tmp = ft_strchr(buffer, '[')))
		return (2);
	*tmp = '\0';
	write = buffer;
	while (write != tmp - 1)
		ioctl(0, TIOCSTI, write++);
	tmp_y = ft_atoi(tmp + 1);
	if (!(tmp = ft_strchr(tmp, ';')))
		return (2);
	*x = ft_atoi(tmp + 1);
	tmp += ft_intlen(*x);
	while (*tmp)
		ioctl(0, TIOCSTI, tmp++);
	*y = tmp_y;
	return (0);
}

/*
** TODO: whatever gets read needs to be put back
*/

int			get_cursor_pos(t_sh *sh, int *x, int *y)
{
	char	buf[31];
	int		ret;
	size_t	i;

	if (sh->prompt_mode == 0)
		return (1);
	ft_memset(buf, 0, 31);
	write(0, "\033[6n", 4);
	i = 0;
	while (i == 0 || (buf[i - 1] != 'R' && i < 30))
	{
		if (!(ret = read(0, buf + i, 1)))
			return (2);
		i++;
	}
	if (i < 2 || read_pos_from_buffer(buf, x, y) || i == 30)
		return (2);
	return (0);
}
