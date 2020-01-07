/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:53:09 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/07 17:50:02 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** TODO: maybe rethink some of these
*/

//(i % n + n) % n;

int	select_handle_arrows(t_prompt *prompt, char *buffer)
{
	t_select *select;

	select = &prompt->select;
	if (buffer[2] == 'A') //up
	{
		/*if (select->selected % select->row_total == 0)
			select->selected += select->row_total - 1;
		else
			select->selected -= 1;
		if (select->selected > select->nb_elem - 1)
			select->selected = select->nb_elem - 1;\*/
		select->selected =
			((select->selected - 1) % select->nb_elem + select->nb_elem) %
			select->nb_elem;
	}
	else if (buffer[2] == 'B') //down
		select->selected = (select->selected + 1) % select->nb_elem;
	else if (buffer[2] == 'C') //right
		if (select->selected > ((select->row_total * select->elem_per_row) - select->row_total - 1))
			select->selected %= select->row_total;
		else
		{
			select->selected += select->row_total;
			if (select->selected > select->nb_elem - 1)
				select->selected = select->nb_elem -1;
		}
	else if (buffer[2] == 'D') //left
		if (select->selected < select->row_total)
		{
			select->selected = (select->row_total * (select->elem_per_row - 1))
				+ (select->selected % select->row_total);
			if (select->selected > select->nb_elem - 1)
				select->selected = select->nb_elem - 1;
		}
		else
			select->selected -= select->row_total;
	else if (buffer[2] == 'H') //should we implement those?
		while (select->selected > select->row_total - 1)
			select->selected -= select->row_total;
	else if (buffer[2] == 'F') //^
	{
		while (select->selected < select->nb_elem)
			select->selected += select->row_total;
		select->selected -= select->row_total;
	}
	else
		return (RET_EXIT_SELECT);
	select_render(prompt, select);
	return (RET_CONT);
}

/*
** TODO: don't calc prompt pos every single time
*/

int		handle_arrows(t_prompt *prompt, char *buffer)
{
	if (buffer[1] != '[')
		return (1);
	if (buffer[2] == 'A')
		; //TODO: Move up
	else if (buffer[2] == 'B')
		; //TODO: Move down
	else if (buffer[2] == 'C')
		move_right(prompt);
	else if (buffer[2] == 'D')
		move_left(prompt);
	else if (buffer[2] == 'H' && prompt->char_index != 0)
	{
		prompt->buffer_index = 0;
		prompt->char_index = 0;
		move_goto(prompt, prompt->prompt_pos); //TODO: home
	}
	else if (buffer[2] == 'F')
	{
		prompt->char_index = ft_wstrlen(prompt->buffer.buffer);
		prompt->buffer_index = ft_wstrindex(prompt->buffer.buffer,
			prompt->char_index) - prompt->buffer.buffer;
		move_goto(prompt, prompt->max_pos);
	}
	return (RET_CONT);
}
