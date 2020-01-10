/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:19:09 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/09 18:57:34 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int					replace_cursor(t_select *select, t_prompt *prompt)
{
	t_pos	pos;

	ft_putstr_fd(tgetstr("cr", NULL), 0);
	pos.x = prompt->select_mode == 2 ? prompt->max_pos.x : select->original_pos.x;
	pos.y = -select->row_total;
	move_cursor(pos);
	return (SH_SUCCESS);
}

 int			print_selected(t_select *select, t_vec *poss, int i)
{
	if (select->selected == i)
	{
		ft_putstr_fd(tgetstr("so", NULL), 0);
		ft_dprintf(0, "%-*s",select->max_len + 2, (char *)ft_vecget(poss, i));
		ft_putstr_fd(tgetstr("se", NULL), 0);
	}
	else
		ft_dprintf(0, "%-*s",select->max_len + 2 ,(char *)ft_vecget(poss, i));
	return (SH_SUCCESS);
}

/*
** TODO: move to render
*/

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
			if (i <= select->nb_elem && ft_vecget(poss, i) != NULL)
			{
				if (selected != -1 && i == selected)
					print_selected(select, poss, i);
				else
					ft_dprintf(0, "%-*s",select->max_len + 2 ,(char *)ft_vecget(poss, i));
			}
			j++;
			i += select->row_total;
		}
		r++;
		if (r == (size_t)select->row_total)
			break;
		ft_dprintf(0, "\n");
		i -= (select->elem_per_row * select->row_total) - 1;
		i = i < 0 ? i + select->row_total : i;
	}
	replace_cursor(select, prompt);
	return (SH_SUCCESS);
}
