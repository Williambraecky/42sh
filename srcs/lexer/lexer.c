/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:06:59 by ntom              #+#    #+#             */
/*   Updated: 2019/11/20 16:06:12 by wbraeckm         ###   ########.fr       */
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

int			lexer(char *line)
{
	t_lexer		lexer;
	int			res;

	if ((res = init_lexer(&lexer, line)) != SH_SUCCESS)
		return (res);
	tokenization(&lexer);
	return (SH_SUCCESS);
}
