/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecresize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:48:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/06/17 19:41:18 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_vec.h"

/*
** NOTE: returns 0 upon success
*/

int		ft_vecresize(t_vec *vec, size_t new_size)
{
	void	**new;

	if (!(new = ft_realloc(vec->vec,
		vec->size_max * sizeof(*(vec->vec)),
		new_size * sizeof(*(vec->vec)))))
	{
		return (1);
	}
	vec->size_max = new_size;
	vec->vec = new;
	return (0);
}
