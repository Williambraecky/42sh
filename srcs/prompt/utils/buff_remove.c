/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:43:31 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/11/25 16:48:03 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int		buff_remove(t_buff *buffer, size_t pos)
{
	size_t	len;

	len = wcharlen(buffer->buffer[pos]);
	ft_memcpy(buffer->buffer + pos, buffer->buffer + pos + len,
		ft_strlen(buffer->buffer + pos + len) + 1);
	buffer->current_size -= len;
	return (SH_SUCCESS);
}
