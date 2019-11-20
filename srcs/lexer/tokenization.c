/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:22:45 by ntom              #+#    #+#             */
/*   Updated: 2019/11/20 16:25:42 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_tdef		g_def_table[] =
{
	{T_NEWLINE, is_newline_token, create_newline_token},
};

size_t		g_size = sizeof(g_def_table) / sizeof(*g_def_table);

t_tdef		*get_next_def(t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (i < g_size)
	{
		if (g_def_table[i].is_tok(lexer))
			return (&g_def_table[i]);
		i++;
	}
	return (NULL);
}

int			tokenization(t_lexer *lexer)
{
	t_tdef	*new_tok_def;

	while (lexer->line[lexer->i])
	{
		if (!(new_tok_def = get_next_def(lexer)))
			return (SH_ERR);
	}
	//TODO: is stack is not empty get rest of line
	return (SH_SUCCESS);
}
