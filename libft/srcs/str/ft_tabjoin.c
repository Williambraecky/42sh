/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:05:02 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/04 16:13:39 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	calc_total_size(char **tab, char *joiner)
{
	size_t	total_size;
	size_t	join_len;
	size_t	current_len;
	size_t	i;

	total_size = 0;
	join_len = ft_strlen(joiner);
	i = 0;
	while (tab[i])
	{
		current_len = ft_strlen(tab[i]);
		total_size += current_len;
		if (tab[i + 1] && (current_len || JOIN_EMPTY))
			total_size += join_len;
		i++;
	}
	return (total_size);
}

char			*ft_tabjoin(char **tab, char *joiner)
{
	size_t	size;
	size_t	current_len;
	size_t	i;
	char	*str;
	size_t	current_str_len;

	size = calc_total_size(tab, joiner);
	if (!(str = ft_strnew(size)))
		return (NULL);
	i = 0;
	current_len = 0;
	current_str_len = 0;
	while (tab[i])
	{
		current_len = ft_strlen(tab[i]);
		ft_strcat(str + current_str_len, tab[i]);
		current_str_len += current_len;
		if (tab[i + 1] && (current_len || JOIN_EMPTY))
		{
			ft_strcat(str + current_str_len, joiner);
			current_str_len += ft_strlen(joiner);
		}
		i++;
	}
	return (str);
}
