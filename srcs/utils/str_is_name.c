/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 19:05:32 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/06 13:55:12 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** NOTE: this functions defines if a string meets the requirements to be a NAME
*/

int		str_is_name(char *str)
{
	if (!*str || ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (0);
		str++;
	}
	return (1);
}
