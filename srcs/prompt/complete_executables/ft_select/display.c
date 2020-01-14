/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:19:09 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/14 22:47:09 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int					replace_cursor(t_select *select, t_prompt *prompt)
{
	t_pos	pos;

	ft_putstr_fd(tgetstr("cr", NULL), 0);
	pos.x = prompt->cursor_pos.x;
	pos.y = -select->row_total;
	move_cursor(pos);
	return (SH_SUCCESS);
}

int					print_selected(t_select *select, t_vec *poss, int i)
{
	if (select->selected == i)
	{
		ft_putstr_fd(tgetstr("so", NULL), 0);
		ft_dprintf(0, "%-*s", select->max_len + 2, (char *)ft_vecget(poss, i));
		ft_putstr_fd(tgetstr("se", NULL), 0);
	}
	else
		ft_dprintf(0, "%-*s", select->max_len + 2, (char *)ft_vecget(poss, i));
	return (SH_SUCCESS);
}

/*
** TODO: move to render
*/

int					print_poss(t_vec *poss, t_select *select, int selected,
		int i)
{
	if (i <= select->nb_elem && ft_vecget(poss, i) != NULL)
	{
		if (selected != -1 && i == selected)
			print_selected(select, poss, i);
		else
			ft_dprintf(0, "%-*s", select->max_len + 2,
				(char *)ft_vecget(poss, i));
	}
	return (SH_SUCCESS);
}

int					get_scroll_limit(t_select *select, int selected,
		t_prompt *prompt)
{
	size_t	current_row;
	int		diff;

	(void)prompt;
	current_row = selected == -1 ? 0 : selected % select->row_total;
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

int					display_poss_scroll(t_select *select, t_vec *poss,
	int selected, t_prompt *prompt)
{
	size_t	r;
	size_t	j;
	int		i;
	size_t	available_row;

	available_row = select->nb_row - (prompt->max_pos.y + 1);
	get_scroll_limit(select, selected, prompt);
//	ft_dprintf(2, "selected = %d -- current_row = %d --scroll_top = %d -- scroll_bottom = %d\n",select->selected,select->selected % select->nb_row, select->scroll_top, select->scroll_bottom);
	i = select->scroll_top;
	r = 0;
	ft_dprintf(0, "\n");
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
		if (r == (size_t)available_row)
			break ;
		ft_dprintf(0, "\n");
		i -= (select->elem_per_row * select->row_total) - 1;
		i = i < 0 ? i + select->row_total : i;
	}
	replace_cursor(select, prompt);
	return (SH_SUCCESS);
}

int					display_poss(t_select *select, t_vec *poss, int selected,
	t_prompt *prompt)
{
	int		i;
	size_t	j;
	size_t	r;

	i = 0;
	r = 0;
	ft_dprintf(0, "\n");
	while (r < (size_t)select->row_total)
	{
		j = 0;
		while (j < (size_t)select->elem_per_row)
		{
			print_poss(poss, select, selected, i);
			j++;
			i += select->row_total;
		}
		r++;
		if (r == (size_t)select->row_total)
			break ;
		ft_dprintf(0, "\n");
		i -= (select->elem_per_row * select->row_total) - 1;
		i = i < 0 ? i + select->row_total : i;
	}
	replace_cursor(select, prompt);
	return (SH_SUCCESS);
}
