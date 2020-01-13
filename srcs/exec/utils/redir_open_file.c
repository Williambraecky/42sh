/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_open_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:42:00 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 18:02:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <unistd.h>
#include <fcntl.h>

static int	get_flags_for_type(t_type type)
{
	if (type == T_GREATER || type == T_GREATER_AND)
		return (O_CREAT | O_TRUNC | O_WRONLY);
	else if (type == T_DOUBLE_GREATER)
		return (O_CREAT | O_APPEND | O_WRONLY);
	return (O_CREAT | O_RDONLY);
}

int			redir_open_file(char *name, t_type type)
{
	int	flag;

	flag = get_flags_for_type(type);
	return (open(name, flag, 0666));
}
