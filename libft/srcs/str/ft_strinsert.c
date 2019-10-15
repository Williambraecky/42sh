/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:09:59 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/15 16:12:10 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinsert(char *base, char *insert, size_t pos)
{
	char	*result;
	size_t	insert_len;
	size_t	final_len;

	insert_len = ft_strlen(insert);
	final_len = ft_strlen(base) + insert_len;
	if (!(result = ft_strnew(final_len)))
		return (NULL);
	ft_strncpy(result, base, pos);
	ft_strcat(result + pos, insert);
	ft_strcat(result + pos + insert_len, base + pos);
	return (result);
}
