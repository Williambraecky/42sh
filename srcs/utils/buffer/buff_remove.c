/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:43:31 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 21:35:44 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	buff_clear(t_buff *buffer)
{
	ft_bzero(buffer->buffer, buffer->size);
	buffer->size = 0;
}

int		buff_nremove(t_buff *buffer, size_t pos, size_t n)
{
	ft_memmove(buffer->buffer + pos, buffer->buffer + pos + n,
		ft_strlen(buffer->buffer + pos + n) + 1);
	buffer->size -= n;
	return (SH_SUCCESS);
}

int		buff_remove(t_buff *buffer, size_t pos)
{
	return (buff_nremove(buffer, pos, wcharlen(buffer->buffer[pos])));
}
