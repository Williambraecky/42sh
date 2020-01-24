/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_cursor_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:31:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/24 23:45:52 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** New method handles tabs and newlines better needs another function to
** calculate prompt position //assumes prompt->prompt_pos is always correct
*/

static size_t	skip_color_code(char *str, size_t pos)
{
	size_t len;

	len = pos + 1;
	if (str[len++] != '[')
		return (1);
	while (ft_isdigit(str[len]))
		len++;
	if (str[len++] != 'm')
		return (1);
	return (len - pos);
}

t_pos			calc_prompt_pos(t_prompt *prompt)
{
	t_pos	pos;
	size_t	i;

	pos = (t_pos){.x = 0, .y = 0};
	i = 0;
	while (prompt->prompt[i])
	{
		if (prompt->prompt[i] == 0x1B)
			i += skip_color_code(prompt->prompt, i);
		else
		{
			transform_pos(prompt, &pos, prompt->prompt[i]);
			i += wcharlen(prompt->prompt[i]);
		}
	}
	return (pos);
}

t_pos			calc_cursor_pos(t_prompt *prompt, size_t written)
{
	t_pos	pos;
	size_t	i;

	pos = prompt->prompt_pos;
	i = 0;
	while (written-- && prompt->buffer.buffer[i])
	{
		transform_pos(prompt, &pos, prompt->buffer.buffer[i]);
		i += wcharlen(prompt->buffer.buffer[i]);
	}
	return (pos);
}
