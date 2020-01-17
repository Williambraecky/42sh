/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_specials.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 19:43:04 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/17 21:48:33 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

static void	handle_quote(t_subst *subst)
{
	subst->err = stack_push_or_pop(&subst->stack, T_QUOTE);
	subst->i++;
}

static void	handle_dquote(t_subst *subst)
{
	subst->err = stack_push_or_pop(&subst->stack, T_DOUBLE_QUOTE);
	subst->i++;
}

static void	handle_backslash(t_subst *subst)
{
	subst->err = buff_nappend(&subst->buffer, subst->str + subst->i + 1, 1);
	subst->i += 2;
}

static void	(*g_special_table[])(t_subst *) =
{
	['\''] = handle_quote,
	['\"'] = handle_dquote,
	['\\'] = handle_backslash,
	['$'] = substitute_param,
	['~'] = substitute_tilde
};

/*
** TODO: handle these ' " \ $ ${ ~
** NOTE: in theory none of them aren't closed (for quotes etc)
**    so we can just use push_or_pop for these
*/

void		subst_handle_specials(t_subst *subst)
{
	g_special_table[(int)subst->str[subst->i]](subst);
}
