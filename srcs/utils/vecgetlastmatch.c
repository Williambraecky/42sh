/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecgetlastmatch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <wdaher-a@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:59:07 by wdaher-a          #+#    #+#             */
/*   Updated: 2020/01/15 16:52:25 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	vecgetlastmatch_index(t_vec *vec, char *find)
{
	int 	i;

	i = vec->size - 1;
	while (i >= 0)
	{
		if (vec->vec[i] && ft_strstartswith(vec->vec[i], find))
			return (i);
		--i;
	}
	return (-1);
}
