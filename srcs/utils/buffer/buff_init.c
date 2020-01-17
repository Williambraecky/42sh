/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 18:17:20 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/17 18:19:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		buff_init_size(t_buff *buffer, size_t size)
{
	if (!(buffer->buffer = ft_strnew(size)))
		return (SH_ERR_MALLOC);
	buffer->size = 0;
	buffer->max_size = size;
	return (SH_SUCCESS);
}

int		buff_init(t_buff *buffer)
{
	return (buff_init_size(buffer, PBUFF_DEF_SIZE));
}
