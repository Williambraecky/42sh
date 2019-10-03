/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeiter_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:23:36 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/08/16 15:45:44 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_tree.h"

void	ft_treeiter_suffix(t_tree *tree, void (*func)())
{
	if (!tree)
		return ;
	ft_treeiter_suffix(tree->left, func);
	ft_treeiter_suffix(tree->right, func);
	func(tree);
}
