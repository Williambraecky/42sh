/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:07:19 by ntom              #+#    #+#             */
/*   Updated: 2019/10/29 17:05:02 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*hquery_prev(t_sh *shell, t_hquery *hquery)
{
	t_vec 	history;
	size_t	last;

	history = shell->history;
	last = hquery->curr_index;
	while (hquery->curr_index--)
	{
		if (ft_strstartswith_ncs
			(shell->history.vec[hquery->curr_index], hquery->query))
			return (shell->history.vec[hquery->curr_index]);
	}
	hquery->curr_index = last;
	return (bell_retnull());
}

char	*hquery_next(t_sh *shell, t_hquery *hquery)
{
	t_vec history;

	history = shell->history;
	if (hquery->curr_index == shell->history.size)
		return (bell_retnull());
	while (hquery->curr_index < shell->history.size)
	{
		if (ft_strstartswith_ncs
			(shell->history.vec[hquery->curr_index], hquery->query))
			return (shell->history.vec[hquery->curr_index]);
		hquery->curr_index++;
	}
	return (hquery->query);
}
