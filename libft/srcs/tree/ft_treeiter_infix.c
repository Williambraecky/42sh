/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeiter_infix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:22:20 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/08/16 15:45:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tree.h"

void	ft_treeiter_infix(t_tree *tree, void (*func)())
{
	if (!tree)
		return ;
	ft_treeiter_infix(tree->left, func);
	func(tree->data);
	ft_treeiter_infix(tree->right, func);
}
