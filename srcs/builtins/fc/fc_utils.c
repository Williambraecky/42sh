/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 02:47:05 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/25 22:35:40 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

size_t		*fc_make_range(size_t first, size_t last)
{
	size_t		*new;
	size_t		len;

	len = first >= last ? first - last : last - first;
	if (!(new = ft_memalloc(sizeof(*new) * (len + 1))))
		return (NULL);
	while (first != last)
		*new++ = first >= last ? first-- : first++;
	*new = first;
	return (new - len);
}

int			fc_ensure_newline(char **command)
{
	char	*new;

	if (!*command)
		return (1);
	if (ft_strlen(*command) == 0 || (*command)[ft_strlen(*command) - 1] != '\n')
	{
		new = ft_strjoin(*command, "\n");
		free(*command);
		if (!new)
			return (1);
		*command = new;
	}
	return (0);
}

char		*fc_get_filename(void)
{
	char	*rand;
	char	*filename;

	if (!(rand = sh_randstr(8, NULL)))
		return (NULL);
	filename = ft_strformat("/tmp/42sh%s", rand);
	free(rand);
	return (filename);
}

char		*file_to_str(int fd)
{
	char	buffer[256];
	char	*tmp;
	char	*new;
	ssize_t	j;

	new = NULL;
	while ((j = read(fd, buffer, 255)) > 0)
	{
		buffer[j] = '\0';
		tmp = new;
		if (tmp)
			tmp = ft_strjoin(tmp, buffer);
		else
			tmp = ft_strdup(buffer);
		if (tmp)
			free(new);
		else
			tmp = new;
		new = tmp;
	}
	if (j < 0)
		ft_strdel(&new);
	return (new);
}
