/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:43:30 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/14 22:58:10 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int	get_column_info(t_select *select)
{
	select->elem_per_row = (select->nb_col - 1) / (select->max_len + 2);
	if (select->elem_per_row)
		select->row_total = (select->nb_elem / select->elem_per_row) + 1;
	return (SH_SUCCESS);
}

/*
** NOTE: we do need to update this for every WINSIZ signal
*/

int			get_display_info(t_select *select, t_prompt *prompt)
{
	int		len;
	size_t	i;

	select->nb_col = prompt->winsize.ws_col;
	select->nb_row = prompt->winsize.ws_row - prompt->max_pos.y;
	i = 0;
	select->max_len = 0;
	select->nb_elem = select->poss.size;
	while (i < select->poss.size)
	{
		len = ft_strlen((char *)ft_vecget(&select->poss, i));
		if (len > select->max_len)
			select->max_len = len;
		i++;
	}
	get_column_info(select);
	return (SH_SUCCESS);
}
