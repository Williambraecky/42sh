/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:43:31 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/18 15:32:11 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	buff_clear(t_buff *buffer)
{
	ft_bzero(buffer->buffer, buffer->size);
	buffer->size = 0;
}

int		buff_remove(t_buff *buffer, size_t pos)
{
	size_t	len;

	if (pos == buffer->size - 1)
	{
		buffer->size--;
		buffer->buffer[buffer->size] = '\0';
		return (SH_SUCCESS);
	}
	len = wcharlen(buffer->buffer[pos]);
	ft_memcpy(buffer->buffer + pos, buffer->buffer + pos + len,
		ft_strlen(buffer->buffer + pos + len) + 1);
	buffer->size -= len;
	return (SH_SUCCESS);
}
