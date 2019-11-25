/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:31:12 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/11/25 16:56:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int	check_size(t_buff *buffer, char *insert)
{
	size_t	len;
	size_t	new_len;
	char	*new;

	len = ft_strlen(insert);
	if (buffer->current_size + len < buffer->max_size)
		return (SH_SUCCESS);
	new_len = buffer->max_size + (buffer->max_size / 2);
	if (new_len == 0)
		new_len = 256;
	if (!(new = ft_realloc(buffer->buffer, buffer->max_size + 1, new_len + 1)))
		return (SH_ERR_MALLOC);
	buffer->buffer = new;
	buffer->max_size = new_len;
	return (SH_SUCCESS);
}

int			buff_insert(t_buff *buffer, char *insert, size_t pos)
{
	size_t	len;

	if (check_size(buffer, insert) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	len = ft_strlen(insert);
	ft_memmove(buffer->buffer + pos + len, buffer->buffer + pos,
		ft_strlen(buffer->buffer + pos));
	ft_memcpy(buffer->buffer + pos, insert, len);
	buffer->current_size += len;
	return (SH_SUCCESS);
}
