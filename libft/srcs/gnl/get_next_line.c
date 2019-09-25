/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 10:51:19 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/08/14 16:09:01 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static t_line	*ft_new_line(const int fd, char *buffer, size_t len)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	if (line == NULL)
		return (NULL);
	line->fd = (int)fd;
	line->str = ft_strdup(buffer);
	line->size = len;
	return (line);
}

static int		ft_clean(void *content, void *data_ref)
{
	t_line	*line;
	int		*fd;

	line = (t_line *)content;
	fd = (int *)data_ref;
	if (line->fd != *fd)
		return (1);
	if (*(line->str) == '\n')
		line->str++;
	if (*(line->str) == '\0')
	{
		line->str -= line->size;
		free(line->str);
		free(line);
		return (0);
	}
	return (1);
}

static char		*ft_join_lines(t_list *list, const int fd, size_t count)
{
	t_line	*line;
	char	*str;
	size_t	nl_index;

	if (!(str = ft_strnew(count)))
		return (NULL);
	while (list != NULL)
	{
		line = (t_line *)list->content;
		if (line->fd == fd)
		{
			nl_index = ft_strfind(line->str, '\n');
			ft_strncat(str, line->str, nl_index);
			line->str += nl_index;
			if (*(line->str) == '\n')
				break ;
		}
		list = list->next;
	}
	return (str);
}

static int		ft_read_next_line(t_list **list, const int fd,
		int *count, char *buffer)
{
	t_list	*current;
	t_line	*l;
	int		j;
	int		i;

	current = *list;
	while (current != NULL)
	{
		l = (t_line *)current->content;
		if (l->fd == fd && (*count += (i = ft_strfind(l->str, '\n'))) >= 0)
			if (l->str[i] == '\n')
				return (1);
		current = current->next;
	}
	while ((j = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[j] = '\0';
		l = ft_new_line(fd, buffer, j);
		ft_lstpushback(list, l, sizeof(t_line));
		free(l);
		*count += (i = ft_strfind(buffer, '\n'));
		if (buffer[i] == '\n')
			break ;
	}
	return (j == -1 ? -1 : (j != 0 || *count != 0));
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*list = NULL;
	char			buffer[BUFF_SIZE + 1];
	int				count;
	int				result;

	if (fd == -1 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	count = 0;
	result = ft_read_next_line(&list, fd, &count, buffer);
	if (result == -1)
		return (-1);
	if (result == 0)
		return (0);
	*line = ft_join_lines(list, fd, (size_t)count);
	ft_lstremoveif(&list, (void *)&fd, &ft_clean);
	return (result);
}
