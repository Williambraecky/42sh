/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 01:09:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/12/01 01:10:39 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushfront(t_list **alst, const void *content, size_t content_size)
{
	t_list	*new;

	if (!(new = ft_lstnew(content, content_size)))
		return ;
	new->next = *alst;
	*alst = new;
}
