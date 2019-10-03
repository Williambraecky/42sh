/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_veciter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:13:20 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/06/17 19:14:10 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vec.h"

void	ft_veciter(t_vec *vec, void (*func_ptr)())
{
	size_t	i;

	i = 0;
	while (i < vec->size)
		func_ptr(vec->vec[i++]);
}
