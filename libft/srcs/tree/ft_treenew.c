/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:26:54 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/08/16 15:34:03 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tree.h"

t_tree	*ft_treenew(void *data)
{
	t_tree	*node;

	if (!(node = (t_tree *)ft_memalloc(sizeof(*node))))
		return (NULL);
	node->data = data;
	return (node);
}
