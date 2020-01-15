/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <wdaher-a@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:50:48 by wdaher-a          #+#    #+#             */
/*   Updated: 2020/01/15 17:51:03 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_fc		*init_fc(t_sh *shell)
{
	t_fc	*ret;

	if (!(ret = (t_fc *)malloc(sizeof(t_fc))))
		return (NULL);
	ret->f = NULL;
	ret->l = NULL;
	ret->old_new = NULL;
	ret->start = 0;
	ret->end = shell->history.size;
	ft_bzero(ret->opt, 6);
	ret->n = 0;
	ret->rev = 0;
	return (ret);
}
