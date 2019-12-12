/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_veccpush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 19:04:24 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/12 16:18:40 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vec.h"

int		ft_veccpush(t_vec *vec, void *ptr, size_t size_ptr)
{
	void	*dup;

	if (!(dup = ft_memdup(ptr, size_ptr)))
		return (1);
	if (ft_vecpush(vec, dup))
	{
		free(dup);
		return (1);
	}
	return (0);
}
