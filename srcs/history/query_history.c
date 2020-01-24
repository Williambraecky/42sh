/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:07:19 by ntom              #+#    #+#             */
/*   Updated: 2020/01/24 18:41:48 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*hquery_cprev(t_sh *shell, t_hquery *hquery)
{
	size_t	last;

	last = hquery->curr_index;
	if (last == shell->history.size + 1)
	{
		hquery->curr_index--;
		if (ft_strstr(hquery->orig, hquery->query))
			return (hquery->query);
	}
	while (hquery->curr_index--)
	{
		if (ft_strstr(shell->history.vec[hquery->curr_index], hquery->query))
			return (shell->history.vec[hquery->curr_index]);
	}
	hquery->curr_index = last;
	return (ring_bell());
}

char	*hquery_prev(t_sh *shell, t_hquery *hquery)
{
	size_t	last;

	last = hquery->curr_index;
	while (hquery->curr_index--)
	{
		if (ft_strstartswith_ncs(shell->history.vec[hquery->curr_index],
			hquery->query))
			return (shell->history.vec[hquery->curr_index]);
	}
	hquery->curr_index = last;
	return (ring_bell());
}

char	*hquery_cnext(t_sh *shell, t_hquery *hquery)
{
	if (hquery->curr_index == shell->history.size)
		return (ring_bell());
	while (hquery->curr_index + 1 < shell->history.size)
	{
		hquery->curr_index++;
		if (ft_strstr(shell->history.vec[hquery->curr_index], hquery->query))
			return (shell->history.vec[hquery->curr_index]);
	}
	return (hquery->orig);
}

char	*hquery_next(t_sh *shell, t_hquery *hquery)
{
	if (hquery->curr_index == shell->history.size)
		return (ring_bell());
	while (hquery->curr_index + 1 < shell->history.size)
	{
		hquery->curr_index++;
		if (ft_strstartswith_ncs(shell->history.vec[hquery->curr_index],
			hquery->query))
			return (shell->history.vec[hquery->curr_index]);
	}
	return (hquery->orig);
}
