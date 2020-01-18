/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bparam_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 23:59:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/18 02:12:02 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_valid_operator(char c)
{
	return (c == '+' || c == '-' || c == '?' ||
		c == '=' || c == '%' || c == '%');
}

void	read_operator(t_subst *subst, t_bparam *bparam)
{
	bparam->colon = bparam->param[bparam->end] == ':';
	bparam->end += bparam->colon;
	if (bparam->param[bparam->end] == '}')
	{
		if (bparam->colon)
			subst->err = SH_ERR_BAD_SUBST;
		return ;
	}
	bparam->operator = bparam->param[bparam->end++];
	if (!is_valid_operator(bparam->operator))
	{
		subst->err = SH_ERR_BAD_SUBST; //TODO: print error
		return ;
	}
	if ((bparam->operator == '%' || bparam->operator == '#') &&
		bparam->param[bparam->end] == bparam->operator)
	{
		bparam->end++;
		bparam->operator++;
	}
	if (!(bparam->word = ft_strndup(bparam->param + bparam->end,
		ft_strlen(bparam->param + bparam->end) - 1)))
		subst->err = SH_ERR_MALLOC;
}
