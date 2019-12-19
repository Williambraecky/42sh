/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_newline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:53:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/19 14:58:30 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** TODO: Append newline to buffer and move prompt to max position + 1y
*/

int	handle_newline(t_prompt *prompt, char *buffer)
{
	(void)buffer;
	if (buff_insert(&prompt->buffer, "\n", ft_strlen(prompt->buffer.buffer))
			!= SH_SUCCESS)
		return (SH_ERR_MALLOC);
	return (RET_NL);
}
