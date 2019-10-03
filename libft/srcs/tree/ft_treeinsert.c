/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeinsert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 15:25:33 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/08/16 15:49:16 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_base_insert(t_tree **root, t_tree *new, int (*cmp)())
{
	if (!*root)
	{
		*root = new;
		return (0);
	}
	if (cmp((*root)->data, new->data) > 0)
		return (ft_base_insert(&((*root)->left), new, cmp));
	return (ft_base_insert(&((*root)->right), new, cmp));
}

/*
** NOTE: returns non zero upon failure, refer to libft_tree.h for error codes
*/

int			ft_treeinsert(t_tree **root, void *content, int (*cmp)())
{
	t_tree	*new;

	if (!(new = ft_treenew(content)))
		return (TREE_NO_MEM);
	ft_base_insert(root, new, cmp);
	return (0);
}
