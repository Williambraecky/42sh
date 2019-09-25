/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 13:25:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/08/13 16:01:49 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_swapunknown(void *a, void *b, size_t len)
{
	void	*tmp;

	if (!(tmp = malloc(len)))
		return ;
	ft_memmove(tmp, a, len);
	ft_memmove(a, b, len);
	ft_memmove(b, tmp, len);
	free(tmp);
}

void		ft_memswap(void *a, void *b, size_t len)
{
	if (len == sizeof(char))
		ft_swapchar((char *)a, (char *)b);
	else if (len == sizeof(short))
		ft_swapshort((short *)a, (short *)b);
	else if (len == sizeof(int))
		ft_swapint((int *)a, (int *)b);
	else if (len == sizeof(long))
		ft_swaplong((long *)a, (long *)b);
	else
		ft_swapunknown(a, b, len);
}
