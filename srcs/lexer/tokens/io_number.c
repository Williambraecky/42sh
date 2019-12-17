/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:38:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/17 15:44:38 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		istok_io_number(t_lexer *lexer)
{
	size_t	i;

	if (!ft_isdigit(lexer->line[lexer->i]))
		return (0);
	i = lexer->i;
	while (ft_isdigit(lexer->line[i]))
		i++;
	return (lexer->line[i] == '>' || lexer->line[i] == '<');
}

int		createtok_io_number(t_lexer *lexer)
{
	t_io_nb	tok;
	size_t	len;

	len = lexer->i;
	while (ft_isdigit(lexer->line[len]))
		len++;
	len -= lexer->i;
	tok.token.size = sizeof(tok);
	tok.token.type = T_IO_NUMBER;
	if (!(tok.token.str = ft_strndup(lexer->line + lexer->i, len)))
		return (SH_ERR_MALLOC);
	tok.token.len = len;
	tok.io_nb = ft_atoi(tok.token.str);
	return (token_process(lexer, (t_token*)&tok));
}
