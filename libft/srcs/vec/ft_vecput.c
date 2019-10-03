/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:15:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/06/17 19:40:25 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vec.h"

/*
** NOTE: function does the same thing as ft_vetset but
** moves every element after pos by 1
*/

int		ft_vecput(t_vec *vec, void *ptr, size_t pos)
{
	void	*prev;

	if (vec->size >= vec->size_max)
		if (ft_vecresize(vec, vec->size_max * 2))
			return (1);
	prev = vec->vec[pos];
	vec->vec[pos] = ptr;
	pos++;
	while (pos < vec->size)
	{
		ptr = vec->vec[pos];
		vec->vec[pos] = prev;
		prev = ptr;
		pos++;
	}
	vec->vec[pos] = prev;
	vec->size++;
	return (0);
}
