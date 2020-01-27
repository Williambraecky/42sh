/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_parambrace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 21:08:52 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 23:04:35 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

static int		var_exists(t_subst *subst, char *str, size_t start)
{
	char	buffer[2];

	buffer[0] = str[start];
	buffer[1] = '\0';
	return (has_var(subst->shell, buffer));
}

static size_t	count_characters(t_subst *subst, char *str, size_t start)
{
	size_t	end;

	end = start;
	if (str[end] == '\0')
		return (0);
	while (str[end])
	{
		if (end == start && !ft_isalpha(str[end]) &&
			str[end] != '_')
			break ;
		else if (!ft_isalnum(str[end]) && str[end] != '_')
			break ;
		end++;
	}
	if (start == end && var_exists(subst, str, start))
		return (1);
	return (end - start);
}

static void		expand_parambrace(t_subst *subst, char *param)
{
	t_bparam	bparam;

	ft_bzero(&bparam, sizeof(bparam));
	bparam.param = param;
	if (param[2] == '#')
		bparam.hashtag = 1;
	bparam.end = count_characters(subst, param, 2 + bparam.hashtag);
	if (!(bparam.key = ft_strndup(param + 2 + bparam.hashtag, bparam.end)))
	{
		subst->err = SH_ERR_MALLOC;
		return ;
	}
	bparam.end += 2 + bparam.hashtag;
	read_operator(subst, &bparam);
	if (!(bparam.word = ft_strndup(bparam.param + bparam.end,
		ft_strlen(bparam.param + bparam.end) - 1)))
		subst->err = SH_ERR_MALLOC;
	if (subst->err == SH_SUCCESS)
		apply_bparam_operator(subst, &bparam);
	if (subst->err == SH_SUCCESS)
		subst->err = buff_append(&subst->buffer, bparam.result);
	free_bparam(&bparam);
}

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
	return (j - subst->i);
}

void			substitute_parambrace(t_subst *subst)
{
	char	*tmp;
	size_t	j;

	j = delimit_parambrace(subst);
	if (subst->err != SH_SUCCESS)
		return ;
	if (!(tmp = ft_strndup(subst->str + subst->i, j)))
	{
		subst->err = SH_ERR_MALLOC;
		return ;
	}
	expand_parambrace(subst, tmp);
	free(tmp);
	subst->i += j;
}
