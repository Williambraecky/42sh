/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treenewcpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:30:08 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/14 16:45:13 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tree.h"

t_tree	*ft_treenewcpy(void *data, size_t size)
{
	t_tree	*node;

	if (!(node = (t_tree *)ft_memalloc(sizeof(t_tree))))
		return (NULL);
	if (data)
		if (!(node->data = ft_memdup(data, size)))
		{
			free(node);
			return (NULL);
		}
	return (node);
}
