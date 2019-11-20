/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:06:59 by ntom              #+#    #+#             */
/*   Updated: 2019/11/19 18:04:21 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void		init_lexer(t_lexer *lexer, char *line)
{
	ft_vecinit(&lexer->tokens);
	lexer->line = line;
	lexer->i = 0;
	ft_vecinit(&lexer->stack);
}

int			lexer(char *line)
{
	t_lexer		lexer;

	init_lexer(&lexer, line);
	tokenization(&lexer);
	return (SH_SUCCESS);
}
