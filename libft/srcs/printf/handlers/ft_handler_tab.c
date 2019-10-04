/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:47:28 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/04 16:52:17 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_handle_joiner(va_list *list, t_flags *flags)
{
	char *str;

	str = ft_arg_for(list, flags);
	if (!str)
		str = ", ";
	flags->joiner = str;
}

void	ft_printf_handle_tab(va_list *list, t_flags *flags)
{
	char **tab;

	tab = ft_arg_for(list, flags);
	while (*tab)
	{
		ft_printf_putstr(*tab, flags);
		if (tab[1] && (ft_strlen(*tab) || JOIN_EMPTY))
			ft_printf_putstr(flags->joiner, flags);
		tab++;
	}
}
