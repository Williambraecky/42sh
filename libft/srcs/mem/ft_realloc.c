/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 13:50:19 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/18 13:55:34 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *old, size_t old_size, size_t new_size)
{
	void	*new;

	if (new_size == 0)
	{
		free(old);
		return (NULL);
	}
	if (!(new = ft_memalloc(new_size)))
		return (NULL);
	if (old)
	{
		ft_memcpy(new, old, ft_min(old_size, new_size));
		free(old);
	}
	return (new);
}
