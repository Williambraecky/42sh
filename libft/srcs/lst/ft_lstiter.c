/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:41:45 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/12 15:54:45 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *alst, void (*f)(t_list *elem))
{
	t_list	*cursor;

	if (alst == NULL)
		return ;
	cursor = alst;
	while (cursor != NULL)
	{
		f(cursor);
		cursor = cursor->next;
	}
}
