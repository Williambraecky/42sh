/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecdestroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 23:07:11 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/06/17 23:08:42 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vec.h"

void	default_vec_destroy_function(void *ptr)
{
	free(ptr);
}

void	ft_vecdestroy(t_vec *vec, void (*func_ptr)())
{
	size_t	i;

	i = 0;
	while (i < vec->size)
	{
		func_ptr(vec->vec[i]);
		i++;
	}
	ft_vecfree(vec);
}
