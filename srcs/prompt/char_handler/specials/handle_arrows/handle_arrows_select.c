/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arrows_select.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:21:43 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/02/04 15:42:35 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static void	select_handle_up_arrow(t_select *select)
{
	select->selected =
		((select->selected - 1) % select->nb_elem + select->nb_elem) %
		ft_max(select->nb_elem, 1);
}

static void	select_handle_right_arrow(t_select *select)
{
	int real_row_total;

	real_row_total = select->scroll ? select->nb_elem /
		ft_max(select->elem_per_row, 1) + 1
	: select->row_total;
	if (select->selected > ((real_row_total * select->elem_per_row)
			- real_row_total - 1))
		select->selected %= ft_max(real_row_total, 1);
	else
	{
		select->selected += real_row_total;
		if (select->selected > select->nb_elem - 1)
			select->selected = select->nb_elem - 1;
	}
}

static void	select_handle_left_arrow(t_select *select)
{
	int real_row_total;

	real_row_total = select->scroll ? select->nb_elem /
		ft_max(select->elem_per_row, 1) + 1
	: select->row_total;
	if (select->selected < real_row_total)
	{
		select->selected = (real_row_total * (select->elem_per_row - 1))
			+ (select->selected % ft_max(real_row_total, 1));
		if (select->selected > select->nb_elem - 1)
			select->selected = select->nb_elem - 1;
	}
	else
		select->selected -= real_row_total;
}

int			select_handle_arrows(t_prompt *prompt, char *buffer)
{
	t_select *select;

	select = &prompt->select;
	if (buffer[2] == 'A')
		select_handle_up_arrow(select);
	else if (buffer[2] == 'B')
		select->selected = (select->selected + 1) % ft_max(select->nb_elem, 1);
	else if (buffer[2] == 'C')
		select_handle_right_arrow(select);
	else if (buffer[2] == 'D')
		select_handle_left_arrow(select);
	else if (buffer[2] == 'H')
		while (select->selected > select->row_total - 1 && select->row_total)
			select->selected -= select->row_total;
	else if (buffer[2] == 'F')
	{
		while (select->selected < select->nb_elem && select->row_total)
			select->selected += select->row_total;
		select->selected -= select->row_total;
	}
	else
		return (PROMPT_EXIT_SELECT);
	select_render(prompt, select);
	return (SH_SUCCESS);
}
