/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freesplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:42:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/08 17:35:21 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freesplit(char **split)
{
	size_t	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		ft_strdel(&split[i++]);
	free(split);
}
