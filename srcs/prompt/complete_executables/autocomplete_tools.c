/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:00:39 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/10 19:15:22 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int		first_word(char *line, size_t i, int first)
{
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ') // pas sur du != ' '
		i++;
	if (line[i])
		first = 0;
	while (line[i])
	{
		if (line[i] == '|' || line[i] == '&' || line[i] == ';')
		{
			i++;
			return (first_word(line, i, 1));
		}
		i++;
	}
	return (first);
}

int		get_path(char **line, char **path)
{
	int		i;

	i = ft_strlen(*line) - 1;
	if (strchr(*line, '/'))
	{
		while (i > 0 && line[0][i] != '/')
			i--;
		*path = ft_strsub(*line, 0, i + 1);
		*line = ft_strdup(*line + i + 1);
		if (!*path || !*line)
			return (SH_ERR_MALLOC);
	}
	else
	{
		*path = ft_strdup(".");
		*line = ft_strdup(*line);
		if (!*path || !*line)
			return (SH_ERR_MALLOC);
	}
	return (SH_SUCCESS);
}

char	*get_cursor_word(char *line, t_prompt *prompt)
{
	int		i;
	int		j;
	char	*word;
	char	*tmp;

	i = (int)prompt->buffer_index - 1;
	j = i;
	if (i == -1)
	{
		if (!(word = ft_strdup("")))
			return (NULL);
		return (word);
	}
	while (i > 0 && line[i] != ' ')
		i--;
	tmp = ft_strsub(line, i, (j - i) + 1);
	if (!tmp || !(word = ft_strtrim(tmp)))
		return (NULL);
	free(tmp);
	prompt->select.cursor_left_len = j - i;
	i = j;
	while (line[j] && line[j] != ' ')
		j++;
	prompt->select.cursor_right_len = j - i - 1;
	return (word);
}

int		autocomplete_poss(char *path, char *start, t_vec *poss)
{
	DIR				*dir;
	struct dirent	*sd;

	dir = opendir(path);
	if (dir == NULL)
		return (SH_ERR_OPEN_DIR);
	while ((sd = readdir(dir)) != NULL)
	{
		if (start && ft_strstartswith(sd->d_name, start))
		{
			if ((ft_strequ(sd->d_name, ".") || ft_strequ(sd->d_name, ".."))
			&& ft_strequ("", start))
				continue;
			if (ft_veccpush(poss, sd->d_name, ft_strlen(sd->d_name) + 1))
			{
				closedir(dir);
				return (SH_ERR_MALLOC);
			}
		}
	}
	closedir(dir);
	return (SH_SUCCESS);
}
