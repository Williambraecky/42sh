/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:58:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/06/17 19:01:08 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vec.h"

int		ft_vecdel(t_vec *vec, size_t pos)
{
	if (pos >= vec->size)
		return (1);
	vec->vec[pos] = NULL;
	while (pos < (vec->size_max - 1))
		vec->vec[pos] = vec->vec[pos + 1];
	vec->vec[pos] = NULL;
	vec->size--;
	if (vec->size && vec->size == vec->size_max / 4)
		ft_vecresize(vec, vec->size_max / 2);
	return (0);
}
