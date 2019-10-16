/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstr_remove_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 00:21:58 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/17 00:41:10 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*wstr_remove_char(char *str, size_t index)
{
	char	*result;
	size_t	charlen;

	charlen = wcharlen(*ft_wstrindex(str, index));
	if (!(result = ft_strnew(ft_strlen(str) - charlen)))
		return (NULL);
	ft_strncpy(result, str, ft_wstrindex(str, index) - str);
	ft_strcat(result, str + (ft_wstrindex(str, index) - str + charlen));
	return (result);
}
