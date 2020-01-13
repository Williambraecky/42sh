/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 18:37:27 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/02 18:39:09 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	syntax_error(t_token *token)
{
	ft_putstr_fd("42sh: parse error near `", 2);
	ft_putstr_fd(token->str, 2);
	ft_putstr_fd("'\n", 2);
}
