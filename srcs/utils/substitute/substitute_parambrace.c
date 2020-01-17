/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_parambrace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 21:08:52 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/17 22:23:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

/*
** NOTE: delimit to where it should stop using the stack
** NOTE: this returns the size starting at ${
*/

static size_t	delimit_parambrace(t_subst *subst)
{
	size_t	j;
	size_t	stack_size;

	j = subst->i + 2;
	stack_size = subst->stack.size;
	subst->err = stack_push(&subst->stack, T_BRACEPARAM);
	while (subst->str[j] && subst->err == SH_SUCCESS &&
		stack_size != subst->stack.size)
	{
		if (!is_escaped(&subst->stack, subst->str, j))
			subst->err = delim_handle_specials(&subst->stack, subst->str, j);
		j++;
	}
	if (!subst->str[j] && stack_size != subst->stack.size)
	{
		ft_dprintf(2, "42sh: parse error\n");
		subst->err = SH_ERR_SYNTAX;
	}
	return (j);
}

void	substitute_parambrace(t_subst *subst)
{
	char	*tmp;
	char	*new;
	size_t	j;

	j = delimit_parambrace(subst);
	if (subst->err != SH_SUCCESS)
		return ;
	if (!(tmp = ft_strndup(subst->str + subst->i, j)))
	{
		subst->err = SH_ERR_MALLOC;
		return ;
	}
	subst->err = expand_param(subst->shell, tmp, &new);
	if (subst->err == SH_SUCCESS)
		subst->err = buff_append(&subst->buffer, new);
	free(tmp);
	subst->i += j;
}
