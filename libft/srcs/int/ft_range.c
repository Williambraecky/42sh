/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 10:00:06 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/14 10:00:11 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		*ft_range(int min, int max)
{
	int *tab;

	if (min >= max || !(tab = (int *)malloc(sizeof(int) * (max - min))))
		return (NULL);
	while (max-- > min)
		tab[max - min] = max;
	return (tab);
}
