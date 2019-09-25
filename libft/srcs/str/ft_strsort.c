/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 17:44:59 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/18 17:52:49 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_partition(char **array, size_t low, size_t high,
		int (*cmp)())
{
	char	*pivot;
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

static void		ft_quicksort(char **array, size_t low, size_t high,
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

void			ft_strsort(char **tab, size_t len, int (*cmp)())
{
	ft_quicksort(tab, 0, len, cmp);
}
