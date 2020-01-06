/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:35:09 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/06 17:36:53 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_partition(void **array, size_t low, size_t high,
		int (*cmp)())
{
	void	*pivot;
	size_t	i;
	size_t	left;

	pivot = array[low];
	left = low;
	i = low + 1;
	while (i < high)
	{
		if (cmp(array[i], pivot) < 0)
		{
			left++;
			ft_memswap(array + i, array + left, sizeof(*array));
		}
		i++;
	}
	ft_memswap(array + low, array + left, sizeof(*array));
	return (left);
}

static void		ft_quicksort(void **array, size_t low, size_t high,
		int (*cmp)())
{
	size_t pivot_location;

	if (low < high)
	{
		pivot_location = ft_partition(array, low, high, cmp);
		ft_quicksort(array, low, pivot_location, cmp);
		ft_quicksort(array, pivot_location + 1, high, cmp);
	}
}

void			ft_ptrsort(void **tab, size_t len, int (*cmp)())
{
	ft_quicksort(tab, 0, len, cmp);
}
