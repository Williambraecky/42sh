/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 00:01:57 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/14 20:42:54 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** TODO: proper full render procedure for select
** NOTE: since rendering the line clears the rest of the screen, the line has to be changed first so `change_line` should be remade aswell
** NOTE: we should probably process informations such as elem_per_row etc here
** NOTE: this function should not disrupt the current cursor position
*/

int		select_update_prompt_info(t_select *select, t_prompt *prompt, char *s)
{
	select->written = ft_wstrlen(s);
	default_char_handler(prompt, s, NULL);
	if (select->shell_var_brace > 0)
	{
		default_char_handler(prompt, "}", NULL);
		select->written += 1;
	}
	return (SH_SUCCESS);
}

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
	while (select->cursor_left_len - select->shell_var_brace > 0)
	{
		handle_backspace(prompt, NULL, NULL);
		select->cursor_left_len--;
	}
	while (select->written)
	{
		handle_backspace(prompt, NULL, NULL);
		select->written--;
	}
	select_update_prompt_info(select, prompt, str);
	return (SH_SUCCESS);
}

int		select_render(t_prompt *prompt, t_select *select)
{
	t_vec	*poss;

	(void)prompt;
	poss = &select->poss;
	get_display_info(select, prompt);
	if (prompt->select_mode == 2)
		change_line(select, prompt);
	if (select->row_total > select->nb_row - prompt->max_pos.y)
		display_poss_scroll(&prompt->select, poss, prompt->select.selected, prompt);
	else
		display_poss(&prompt->select, poss, prompt->select.selected, prompt);
	return (SH_SUCCESS);
}
