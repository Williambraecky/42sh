/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 18:11:32 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 23:01:49 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

static char		*g_special_charset = "\'\"\\$~";

static int		is_special(t_subst *subst, size_t j)
{
	char	*tmp;

	if (is_escaped(&subst->stack, subst->str, j))
		return (0);
	tmp = ft_strchr(g_special_charset, subst->str[j]);
	if (!tmp || *tmp == '\0')
		return (0);
	if (*tmp == '~')
		return (tilde_check(subst, j));
	else if (*tmp == '\'' || *tmp == '\"' || *tmp == '\\')
		return (subst->profile & SUB_QUOTE);
	else if (*tmp == '$' && subst->str[j + 1] != '(')
		return ((subst->profile & SUB_PARAM));
	else if (*tmp == '$' && subst->str[j + 1] == '(')
		return ((subst->profile & SUB_CMDSUBST));
	return (0);
}

/*
** NOTE: returns offset
*/

static size_t	next_special(t_subst *subst)
{
	size_t	j;

	j = subst->i;
	while (subst->str[j] && !is_special(subst, j))
		j++;
	return (j - subst->i);
}

static void		handle_non_special(t_subst *subst, int len)
{
	int	ret;

	if ((ret = buff_nappend(&subst->buffer, subst->str + subst->i, len))
		!= SH_SUCCESS)
		subst->err = ret;
	subst->i += len;
}

static int		init_subst(t_subst *subst, t_sh *shell, char *str, int profile)
{
	ft_bzero(subst, sizeof(*subst));
	subst->err = SH_SUCCESS;
	subst->shell = shell;
	subst->str = str;
	subst->profile = profile;
	if (ft_vecinit_size(&subst->stack, ft_strlen(str))
		|| buff_init(&subst->buffer) != SH_SUCCESS)
	{
		free_subst(subst);
		return (SH_ERR_MALLOC);
	}
	return (SH_SUCCESS);
}

int				substitute(t_sh *shell, char *str, char **result, int profile)
{
	t_subst	subst;
	size_t	next;

	if (init_subst(&subst, shell, str, profile) != SH_SUCCESS)
		return (SH_ERR_MALLOC);
	while (str[subst.i] && subst.err == SH_SUCCESS)
	{
		if ((next = next_special(&subst)) != 0)
			handle_non_special(&subst, next);
		else
			subst_handle_specials(&subst);
	}
	if (subst.err == SH_SUCCESS)
		if (!(*result = ft_strdup(subst.buffer.buffer)))
			subst.err = SH_ERR_MALLOC;
	free_subst(&subst);
	return (subst.err);
}
