/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 23:27:36 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/24 23:35:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_u64	g_next = 1;
static char		*g_def_charset = "abcdefghijklmnopqrstuvwxyz1234567890";

/*
** NOTE: pseudo random generation
*/

int				sh_rand(void)
{
	g_next = g_next * 1103515245 + 12345;
	return ((unsigned int)(g_next / 65536) % 32768);
}

int				sh_rand_range(int min, int max)
{
	if (max - min == 0)
		return (0);
	return (min + sh_rand() % (max - min));
}

void			sh_srand(t_u64 seed)
{
	g_next = seed;
}

char			*sh_randstr(size_t len, char *charset)
{
	size_t		set_len;
	char		*new;

	if (!charset || ft_strlen(charset) == 0)
		charset = g_def_charset;
	set_len = ft_strlen(charset);
	if (!(new = ft_strnew(len)))
		return (NULL);
	while (len--)
		new[len] = charset[sh_rand() % set_len];
	return (new);
}
