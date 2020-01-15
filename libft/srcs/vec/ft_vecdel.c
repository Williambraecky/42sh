/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:58:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/15 17:07:39 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vec.h"

int		ft_vecdel(t_vec *vec, size_t pos)
{
	if (pos >= vec->size)
		return (1);
	vec->vec[pos] = NULL;
	while (pos < (vec->size_max - 1))
	{
		vec->vec[pos] = vec->vec[pos + 1];
		pos++;
	}
	vec->vec[pos] = NULL;
	vec->size--;
	return (0);
}
