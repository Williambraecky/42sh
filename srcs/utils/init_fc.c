/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <wdaher-a@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:50:48 by wdaher-a          #+#    #+#             */
/*   Updated: 2020/01/21 18:18:29 by wdaher-a         ###   ########.fr       */
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
	get_internal(shell, "fcedit", &ret->ed);
	return (ret);
}

int		free_fc(t_fc *fc)
{
	if (fc->f)
		ft_strdel(&fc->f);
	if (fc->l)
		ft_strdel(&fc->l);
	if (fc->old_new)
		ft_freesplit(fc->old_new);
	if (fc->ed)
		ft_strdel(&fc->ed);
	ft_bzero(fc->opt, 6);
	return (SH_SUCCESS);
}
