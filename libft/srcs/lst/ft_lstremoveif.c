/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremoveif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 11:57:35 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/21 10:24:44 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstremoveif(t_list **alst, void *data_ref, int (*cmp)())
{
	t_list *current;
	t_list *prev;

	if (alst == NULL)
		return ;
	current = *alst;
	while (current != NULL)
	{
		if (cmp(current->content, data_ref) == 0)
		{
			if (current == *alst)
			{
				*alst = current->next;
				free(current);
				current = *alst;
				continue ;
			}
			else
				prev->next = current->next;
			free(current);
			current = prev;
		}
		prev = current;
		current = current->next;
	}
}
