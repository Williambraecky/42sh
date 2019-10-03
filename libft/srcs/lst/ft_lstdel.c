/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:30:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/04/25 16:59:22 by jstraetm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;
	t_list	*cursor;

	if (alst == NULL)
		return ;
	cursor = *alst;
	while (cursor != NULL)
	{
		next = cursor->next;
		del(cursor->content, cursor->content_size);
		free(cursor);
		cursor = next;
	}
	*alst = NULL;
}
