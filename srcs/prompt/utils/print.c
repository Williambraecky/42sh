/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:51:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/17 01:29:35 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	print_buffer(t_prompt *prompt)
{
	t_pos	new;

	new = calc_cursor_pos(prompt,
		prompt->prompt_len + ft_wstrlen(prompt->buffer));
	new.x -= prompt->cursor_pos.x;
	new.y -= prompt->cursor_pos.y;
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_putstr_fd(ft_wstrindex(prompt->buffer, prompt->char_index), 0);
	move_cursor(new);
}
