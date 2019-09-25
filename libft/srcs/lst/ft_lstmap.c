/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:48:09 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/14 08:03:45 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *cursor;

	if (lst == NULL)
		return (NULL);
	new = f(lst);
	cursor = new;
	lst = lst->next;
	while (lst != NULL && cursor != NULL)
	{
		cursor->next = f(lst);
		if (cursor->next == NULL)
			return (NULL);
		cursor = cursor->next;
		lst = lst->next;
	}
	return (new);
}
