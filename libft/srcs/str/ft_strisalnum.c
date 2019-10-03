/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisalnum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcastron <tcastron@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 11:48:04 by tcastron          #+#    #+#             */
/*   Updated: 2019/05/08 11:48:59 by tcastron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strisalnum(const char *str)
{
	while (*str)
		if (!ft_isalnum(*str++))
			return (0);
	return (1);
}
