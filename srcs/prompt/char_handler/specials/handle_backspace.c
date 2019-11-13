/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backspace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:54:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/11/13 16:15:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	handle_backspace(t_prompt *prompt, char *buffer)
{
	char	*result;

	(void)buffer;
	if (prompt->char_index == 0)
		return (RET_CONT);
	if (!(result = wstr_remove_char(prompt->buffer, prompt->char_index - 1)))
	{
		ft_strdel(&prompt->buffer);
		return (RET_ERR);
	}
	ft_strdel(&prompt->buffer);
	prompt->buffer = result;
	move_left(prompt, 1);
	return (RET_CONT | RET_REPRINT);
}
