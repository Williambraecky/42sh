/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeiter_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:19:53 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/08/16 15:45:38 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tree.h"

void	ft_treeiter_prefix(t_tree *tree, void (*func)())
{
	if (!tree)
		return ;
	func(tree->data);
	ft_treeiter_prefix(tree->left, func);
	ft_treeiter_prefix(tree->right, func);
}
