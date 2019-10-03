/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisascii.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcastron <tcastron@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:59:28 by tcastron          #+#    #+#             */
/*   Updated: 2019/05/02 12:01:21 by tcastron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strisascii(const char *str)
{
	while (*str)
		if (!ft_isascii(*str++))
			return (0);
	return (1);
}
