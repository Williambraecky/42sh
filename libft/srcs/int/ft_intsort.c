/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 18:43:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/28 19:14:56 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_partition(int *tab, size_t low, size_t high, int (*cmp)())
{
	int		pivot;
	size_t	i;
	size_t	left;

	pivot = tab[low];
	left = low;
	i = low + 1;
	while (i < high)
	{
		if (cmp(tab[i], pivot) < 0)
			ft_swapint(&(tab[i]), &(tab[++left]));
		i++;
	}
	ft_swapint(tab + low, tab + left);
	return (left);
}

static void		ft_quicksort(int *tab, size_t low, size_t high, int (*cmp)())
{
	size_t pivot;

	if (low < high)
	{
		pivot = ft_partition(tab, low, high, cmp);
		ft_quicksort(tab, low, pivot, cmp);
		ft_quicksort(tab, pivot + 1, high, cmp);
	}
}

void			ft_intsort(int *tab, size_t len, int (*cmp)())
{
	ft_quicksort(tab, 0, len, cmp);
}
