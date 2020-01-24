/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bparam_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 23:59:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/24 23:36:59 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_valid_operator(char c)
{
	return (c == '+' || c == '-' || c == '?' ||
		c == '=' || c == '%' || c == '#');
}

void	read_operator(t_subst *subst, t_bparam *bparam)
{
	bparam->colon = bparam->param[bparam->end] == ':';
	bparam->end += bparam->colon;
	if (bparam->param[bparam->end] == '}')
	{
		if (bparam->colon)
		{
			ft_dprintf(2, "42sh: unrecognized modified\n");
			subst->err = SH_ERR_BAD_SUBST;
		}
		return ;
	}
	bparam->operator = bparam->param[bparam->end++];
	if (!is_valid_operator(bparam->operator))
	{
		ft_dprintf(2, "42sh: unknown operator: %c\n", bparam->operator);
		subst->err = SH_ERR_BAD_SUBST;
		return ;
	}
	if ((bparam->operator == '%' || bparam->operator == '#') &&
		bparam->param[bparam->end] == bparam->operator)
	{
		bparam->end++;
		bparam->operator++;
	}
}
