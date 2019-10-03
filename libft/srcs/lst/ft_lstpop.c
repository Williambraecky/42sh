/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 15:09:06 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/30 15:10:56 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop(t_list **list, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (!list || !*list)
		return ;
	tmp = *list;
	*list = (*list)->next;
	del(tmp->content, tmp->content_size);
	free(tmp);
}
