/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:38:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/12/19 17:53:24 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		istok_io_number(t_lexer *lexer, t_token *token)
{
	size_t	i;
	char	c;

	if (!ft_isdigit(token->str[0]))
		return (0);
	i = 0;
	while (ft_isdigit(token->str[i]))
		i++;
	c = *(lexer->line + lexer->i + i);
	return (c == '>' || c == '<');
}

int		transform_io_number(t_lexer *lexer, t_token *token)
{
	t_io_nb	tok;

	tok.token = *token;
	tok.token.type = T_IO_NUMBER;
	tok.token.size = sizeof(tok);
	tok.io_nb = ft_atoi(tok.token.str);
	return (token_process(lexer, (t_token*)&tok));
}
