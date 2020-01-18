/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:31:12 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/18 21:56:46 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int	check_size(t_buff *buffer, size_t n)
{
	size_t	len;
	size_t	new_len;
	char	*new;

	len = n;
	if (buffer->size + len < buffer->max_size)
		return (SH_SUCCESS);
	new_len = buffer->max_size * 2;
	if (new_len == 0)
		new_len = 256;
	while (buffer->size + len >= new_len)
		new_len *= 2;
	if (!(new = ft_realloc(buffer->buffer, buffer->max_size + 1, new_len + 1)))
		return (SH_ERR_MALLOC);
	buffer->buffer = new;
	buffer->max_size = new_len;
	return (SH_SUCCESS);
}

int			buff_ninsert(t_buff *buffer, char *insert, size_t pos, size_t n)
{
	size_t	len;

	len = ft_min(n, ft_strlen(insert));
	if (check_size(buffer, len) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	ft_memmove(buffer->buffer + pos + len, buffer->buffer + pos,
		ft_strlen(buffer->buffer + pos));
	ft_memcpy(buffer->buffer + pos, insert, len);
	buffer->size += len;
	buffer->buffer[buffer->size] = '\0';
	return (SH_SUCCESS);
}

int			buff_insert(t_buff *buffer, char *insert, size_t pos)
{
	return (buff_ninsert(buffer, insert, pos, ft_strlen(insert)));
}

int			buff_nappend(t_buff *buffer, char *str, size_t n)
{
	return (buff_ninsert(buffer, str, buffer->size, n));
}

int			buff_append(t_buff *buffer, char *str)
{
	return (buff_insert(buffer, str, buffer->size));
}
