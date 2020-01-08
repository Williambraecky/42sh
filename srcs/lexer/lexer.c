/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:06:59 by ntom              #+#    #+#             */
/*   Updated: 2020/01/08 16:28:54 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			init_lexer(t_lexer *lexer, char *line)
{
	ft_bzero(lexer, sizeof(*lexer));
	if (ft_vecinit(&lexer->tokens))
		return (SH_ERR_MALLOC);
	if (!(lexer->line = ft_strdup(line)))
		return (SH_ERR_MALLOC);
	lexer->line_size = ft_strlen(line);
	lexer->i = 0;
	if (ft_vecinit_size(&lexer->stack, ft_strlen(lexer->line) / 2))
		return (SH_ERR_MALLOC);
	lexer->stack_completed = 0;
	return (SH_SUCCESS);
}

int			lexer(char *line, t_lexer *lex)
{
	t_lexer		lexer;
	int			res;
	char		*groups;

	groups = NULL;
	if ((res = init_lexer(&lexer, line)) != SH_SUCCESS)
		return (res);
	if ((res = tokenization(&lexer)) != SH_SUCCESS)
	{
		lexer_free(&lexer);
		return (res);
	}
	*lex = lexer;
	return (SH_SUCCESS);
}
