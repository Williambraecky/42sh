/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_bparam_operator2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 00:37:50 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/20 20:22:31 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	apply_hashtag_flag(t_subst *subst, t_bparam *bparam)
{
	char	*new;
	size_t	len;

	len = ft_strlen(bparam->result);
	if (!(new = ft_uitoa(len)))
	{
		subst->err = SH_ERR_MALLOC;
		return ;
	}
	free(bparam->result);
	bparam->result = new;
}

/*
** NOTE: this is a really really basic implementation they do not actually match
**   but rather remove start or end of string depending on which operator it is
*/

void	apply_hashtag(t_subst *subst, t_bparam *bparam)
{
	char	*pattern;

	subst->err = substitute(subst->shell, bparam->word, &pattern, ~SUB_ASSIGN);
	if (subst->err != SH_SUCCESS)
		return ;
	bparam->result = ft_strsrepl(bparam->val, pattern, "");
	free(pattern);
	if (!bparam->result)
		subst->err = SH_ERR_MALLOC;
}

void	apply_percent(t_subst *subst, t_bparam *bparam)
{
	char	*pattern;
	size_t	len;

	subst->err = substitute(subst->shell, bparam->word, &pattern, ~SUB_ASSIGN);
	if (subst->err != SH_SUCCESS)
		return ;
	len = ft_strlen(bparam->val);
	while (len--)
	{
		if (ft_strstartswith(bparam->val + len, pattern))
		{
			bparam->result = ft_strndup(bparam->val, len);
			if (!bparam->result)
				subst->err = SH_ERR_MALLOC;
			break ;
		}
	}
	if (subst->err == SH_SUCCESS && !bparam->result)
		bparam->result = ft_strdup("");
	if (!bparam->result)
		subst->err = SH_ERR_MALLOC;
}
