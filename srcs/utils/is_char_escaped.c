/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_char_escaped.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:51:14 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/08 14:52:08 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_char_escaped(char *str, int index)
{
	if (!str || index == 0)
		return (0);
	return (str[index - 1] == '\\' && !is_char_escaped(str, index - 1));
}
