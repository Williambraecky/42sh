/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:24:52 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/12 15:31:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*cursor;

	if (alst == NULL || *alst == NULL)
		return ;
	cursor = *alst;
	del(cursor->content, cursor->content_size);
	free(cursor);
	*alst = NULL;
}
