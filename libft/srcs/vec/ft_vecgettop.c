/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecgettop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:55:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/12 15:55:59 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_vecgettop(t_vec *vec)
{
	if (!vec || vec->size == 0)
		return (NULL);
	return (vec->vec[vec->size - 1]);
}
