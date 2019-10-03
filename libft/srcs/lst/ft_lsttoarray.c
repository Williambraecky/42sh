/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 18:06:13 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/05/16 20:02:23 by jstraetm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_freeresult(void **result)
{
	size_t	i;

	i = 0;
	while (result[i])
		free(result[i++]);
	free(result);
}

void		**ft_lsttoarray(t_list *list)
{
	void	**result;
	size_t	len;
	size_t	i;

	len = ft_lstlen(list);
	if (list == NULL || !(result = ft_memalloc(sizeof(*result) * (len + 1))))
		return (NULL);
	i = 0;
	result[len] = NULL;
	while (len--)
	{
		if (!(result[i] = malloc(list->content_size)))
		{
			ft_freeresult(result);
			return (NULL);
		}
		ft_memcpy(result[i], list->content, list->content_size);
		list = list->next;
		i++;
	}
	return (result);
}
