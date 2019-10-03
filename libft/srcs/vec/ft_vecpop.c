/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:05:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/06/17 19:10:21 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vec.h"

void	*ft_vecpop(t_vec *vec)
{
	if (vec->size)
	{
		vec->size--;
		return (vec->vec[vec->size]);
	}
	return (NULL);
}
