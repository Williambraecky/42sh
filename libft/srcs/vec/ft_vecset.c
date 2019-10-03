/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:10:49 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/06/17 19:11:31 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vec.h"

int		ft_vecset(t_vec *vec, void *ptr, size_t pos)
{
	if (pos >= vec->size_max)
		return (1);
	vec->vec[pos] = ptr;
	return (0);
}
