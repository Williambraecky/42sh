/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcountchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:29:43 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/29 15:30:40 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcountchar(char *str, char c)
{
	size_t	i;

	i = 0;
	while (*str)
		if (*str++ == c)
			i++;
	return (i);
}
