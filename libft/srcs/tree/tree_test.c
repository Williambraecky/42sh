/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 15:42:01 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/08/16 15:49:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void tree_iter(int *data)
{
	ft_printf("Data : %d\n", *data);
}

int main(void)
{
	t_tree	*tree;
	int		*data;
	int		i;

	tree = NULL;
	i = 0;
	while (i < 100)
	{
		data = malloc(sizeof(i));
		*data = i++;
		ft_treeinsert(&tree, data, ft_intcmp);
	}
	ft_treeiter_infix(tree, tree_iter);
}
