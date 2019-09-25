/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_printed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 16:43:06 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/09/14 12:31:35 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_handle_printed(va_list *list, t_flags *flags)
{
	size_t	*n;

	n = (size_t *)ft_arg_for(list, flags);
	if (flags->longnb >= 2)
		*n = (size_t)flags->printed;
	else if (flags->longnb == 1)
		*((long int *)n) = ((long int)flags->printed);
	else if (flags->shortnb >= 2)
		*((char *)n) = ((char)flags->printed);
	else if (flags->shortnb == 1)
		*((short int *)n) = ((short int)flags->printed);
	else
		*((int *)n) = flags->printed;
}
