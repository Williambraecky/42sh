/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:55:45 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/06/17 18:57:34 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vec.h"

/*
** NOTE: returns 0 upon success
*/

int		ft_vecpush(t_vec *vec, void *ptr)
{
	if (vec->size >= vec->size_max)
		if (ft_vecresize(vec, vec->size_max * 2))
			return (1);
	vec->vec[vec->size++] = ptr;
	return (0);
}
