/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:04:05 by ntom              #+#    #+#             */
/*   Updated: 2019/11/19 18:24:05 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			new_line_token(t_lexer *lexer)
{
	if (lexer->line[lexer->i] == '\n')
		return (1);
	return (0);
}
