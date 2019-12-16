/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:06:59 by ntom              #+#    #+#             */
/*   Updated: 2019/12/16 17:42:06 by wbraeckm         ###   ########.fr       */
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
	lexer->i = 0;
	if (ft_vecinit(&lexer->stack))
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

/*
** NOTE: complete prompt should be used to know if we have to restart a prompt
**  in the case of unfinished quotes/dquotes for example;
**  should be 0 when parsing aliases etc
*/

int			lexer(char *line, t_lexer *lex, int complete_prompt)
{
	t_lexer		lexer;
	int			res;

	(void)complete_prompt;
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
