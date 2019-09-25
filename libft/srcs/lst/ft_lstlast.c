/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:06:05 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/14 14:07:25 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list **alst)
{
	t_list	*current;

	if (alst == NULL || *alst == NULL)
		return (NULL);
	current = *alst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}
