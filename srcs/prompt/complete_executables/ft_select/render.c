/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 00:01:57 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/10 18:16:27 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** TODO: proper full render procedure for select
** NOTE: since rendering the line clears the rest of the screen, the line has to be changed first so `change_line` should be remade aswell
** NOTE: we should probably process informations such as elem_per_row etc here
** NOTE: this function should not disrupt the current cursor position
*/

int		change_line(t_select *select, t_prompt *prompt)
{
	char	*str;

	str = (char*)ft_vecget(&select->poss, select->selected);
	while (select->cursor_right_len > 0)
	{
		move_right(prompt);
		handle_backspace(prompt, NULL, NULL);
		select->cursor_right_len--;
	}
	while (/*select->file_complete && */select->cursor_left_len + 1)
	{
		handle_backspace(prompt, NULL, NULL);
		select->cursor_left_len--;
	}
	while (select->written)
	{
		move_right(prompt);
		handle_backspace(prompt, NULL, NULL);
		select->written--;
	}
	select->written = ft_wstrlen(str);
	default_char_handler(prompt, str, NULL);
	return (0);
}

int		select_render(t_prompt *prompt, t_select *select)
{
	t_vec	*poss;

	(void)prompt;
	poss = &select->poss;
	get_display_info(select, prompt);
	if (prompt->select_mode == 2)
		change_line(select, prompt);
	display_poss(&prompt->select, poss, prompt->select.selected, prompt);
	return (SH_SUCCESS);
}
