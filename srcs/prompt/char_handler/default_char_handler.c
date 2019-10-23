/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_char_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:54:46 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/23 15:55:08 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	default_char_handler(t_prompt *prompt, char *buffer)
{
	char	*result;

	if (!(result =
		ft_strinsert(prompt->buffer, buffer, prompt->buffer_index)))
	{
		ft_strdel(&prompt->buffer);
		return (RET_ERR);
	}
	ft_strdel(&prompt->buffer);
	prompt->buffer = result;
	prompt->buffer_index += wcharlen(*buffer);
	prompt->char_index++;
	return (RET_PRINT | RET_CONT);
}
