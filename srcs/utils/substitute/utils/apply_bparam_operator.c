/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_bparam_operator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 23:34:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 22:31:29 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	apply_minus(t_subst *subst, t_bparam *bparam)
{
	if (!bparam->unset && bparam->val && *bparam->val != '\0')
		bparam->result = ft_strdup(bparam->val);
	else
	{
		if (!bparam->colon && !bparam->unset &&
			(!bparam->val || ft_strlen(bparam->val) == 0))
			bparam->result = ft_strdup("");
		else
		{
			subst->err = substitute(subst->shell, bparam->word,
				&bparam->result, ~SUB_ASSIGN);
		}
	}
}

static void	apply_equals(t_subst *subst, t_bparam *bparam)
{
	if (!bparam->unset && bparam->val && *bparam->val != '\0')
		bparam->result = ft_strdup(bparam->val);
	else
	{
		if (bparam->colon)
		{
			subst->err = substitute(subst->shell, bparam->word,
				&bparam->result, ~SUB_ASSIGN);
			if (subst->err == SH_SUCCESS)
				subst->err = add_var(subst->shell, bparam->key,
					bparam->result);
		}
		else if (bparam->unset)
		{
			bparam->result = ft_strdup("");
			subst->err = add_var(subst->shell, bparam->key,
				bparam->result);
		}
		else
			bparam->result = ft_strdup(bparam->val);
	}
}

static void	apply_qmark(t_subst *subst, t_bparam *bparam)
{
	if (!bparam->unset && bparam->val && *bparam->val != '\0')
		bparam->result = ft_strdup(bparam->val);
	else
	{
		if (!bparam->colon && !bparam->unset &&
			(!bparam->val || ft_strlen(bparam->val) == 0))
			bparam->result = ft_strdup("");
		else
		{
			if (bparam->word && ft_strlen(bparam->word) != 0)
				ft_dprintf(2, "42sh: %s: %s\n", bparam->key, bparam->word);
			else
				ft_dprintf(2, "42sh: %s: parameter not set\n", bparam->key);
			subst->err = SH_ERR_BAD_SUBST;
			return ;
		}
	}
}

static void	apply_plus(t_subst *subst, t_bparam *bparam)
{
	if (!bparam->unset && bparam->val && *bparam->val != '\0')
		subst->err = substitute(subst->shell, bparam->word,
			&bparam->result, ~SUB_ASSIGN);
	else
	{
		if (!bparam->colon && !bparam->unset &&
			(!bparam->val || ft_strlen(bparam->val) == 0))
			subst->err = substitute(subst->shell, bparam->word,
				&bparam->result, ~SUB_ASSIGN);
		else
		{
			bparam->result = ft_strdup("");
		}
	}
}

void		apply_bparam_operator(t_subst *subst, t_bparam *bparam)
{
	if (get_var(subst->shell, bparam->key, &bparam->val) != SH_SUCCESS)
	{
		bparam->val = "";
		bparam->unset = 1;
	}
	if (bparam->operator == 0)
	{
		if (!(bparam->result = ft_strdup(bparam->val)))
			subst->err = SH_ERR_MALLOC;
	}
	else if (bparam->operator == '-')
		apply_minus(subst, bparam);
	else if (bparam->operator == '+')
		apply_plus(subst, bparam);
	else if (bparam->operator == '?')
		apply_qmark(subst, bparam);
	else if (bparam->operator == '=')
		apply_equals(subst, bparam);
	else if (bparam->operator == '%' || bparam->operator == '%' + 1)
		apply_percent(subst, bparam);
	else if (bparam->operator == '#' || bparam->operator == '#' + 1)
		apply_hashtag(subst, bparam);
	if (subst->err == SH_SUCCESS && bparam->hashtag)
		apply_hashtag_flag(subst, bparam);
}
