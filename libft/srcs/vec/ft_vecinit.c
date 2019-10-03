/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:36:49 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/06/17 14:39:42 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vec.h"

void	ft_vecinit(t_vec *vec)
{
	vec->size = 0;
	vec->size_max = VEC_DEF_SIZE;
	vec->vec = (void**)ft_memalloc(sizeof(*vec->vec) * vec->size_max);
}
