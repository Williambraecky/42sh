/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_scroll.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:34:56 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/02/04 15:24:55 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int					get_scroll_limit(t_select *select, int selected,
		t_prompt *prompt)
{
	size_t	current_row;
	int		diff;

	(void)prompt;
	current_row = selected == -1 ? 0 : selected % ft_max(select->row_total, 1);
	if (current_row < select->scroll_top)
	{
		diff = select->scroll_top - current_row;
		select->scroll_top -= diff;
		select->scroll_bottom -= diff;
	}
	else if (current_row >= select->scroll_bottom)
	{
		diff = current_row - select->scroll_bottom + 1;
		select->scroll_top += diff;
		select->scroll_bottom += diff;
	}
	return (SH_SUCCESS);
}

int					prepare_loop(int *available_row, int *i,
	t_prompt *prompt, int *r)
{
	t_select *select;

	select = &prompt->select;
	*available_row = select->nb_row - (prompt->max_pos.y + 1);
	get_scroll_limit(select, select->selected, prompt);
	*i = select->scroll_top;
	*r = 0;
	ft_dprintf(0, "\n");
	return (SH_SUCCESS);
}

int					display_poss_scroll(t_select *select, t_vec *poss,
	int selected, t_prompt *prompt)
{
	int		r;
	size_t	j;
	int		i;
	int		available_row;

	prepare_loop(&available_row, &i, prompt, &r);
	while (r < available_row)
	{
		j = 0;
		while (j < (size_t)select->elem_per_row)
		{
			print_poss(poss, select, selected, i);
			j++;
			i += select->row_total;
		}
		r++;
		if (r == available_row)
			break ;
		ft_dprintf(0, "\n");
		i -= (select->elem_per_row * select->row_total) - 1;
		i = i < 0 ? i + select->row_total : i;
	}
	select->row_total = available_row;
	replace_cursor(select, prompt);
	return (SH_SUCCESS);
}
