/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:53:18 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/06/17 18:55:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vec.h"

void	*ft_vecget(t_vec *vec, size_t pos)
{
	if (pos < vec->size)
		return (vec->vec[pos]);
	return (NULL);
}
