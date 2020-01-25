/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:59:32 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/25 21:13:04 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	default_free(t_token *token)
{
	ft_strdel(&token->str);
	free(token);
}

static void	hdoc_free(t_hdoc *doc)
{
	ft_strdel(&doc->name);
	ft_strdel(&doc->content);
	default_free((t_token*)doc);
}

void		(*g_dispatch_free[])() =
{
	[T_DOUBLE_LESSER] = hdoc_free,
	[T_NULL] = default_free
};

void		token_free(t_token *token)
{
	if ((t_u64)token->type <
		(sizeof(g_dispatch_free) / sizeof(*g_dispatch_free))
		&& g_dispatch_free[token->type])
		g_dispatch_free[token->type](token);
	else
		default_free(token);
}
