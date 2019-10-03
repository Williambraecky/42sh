/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_veciteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:14:22 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/06/17 19:21:35 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vec.h"

void	ft_veciteri(t_vec *vec, void (*func_ptr)(void *, size_t))
{
	size_t	i;

	i = 0;
	while (i < vec->size)
	{
		func_ptr(vec->vec[i], i);
		i++;
	}
}
