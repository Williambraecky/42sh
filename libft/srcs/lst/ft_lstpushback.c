/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 08:27:54 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/18 23:58:51 by rchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list **alst, const void *content, size_t content_size)
{
	t_list *last;

	last = *alst;
	if (last == NULL)
	{
		*alst = ft_lstnew(content, content_size);
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = ft_lstnew(content, content_size);
}
