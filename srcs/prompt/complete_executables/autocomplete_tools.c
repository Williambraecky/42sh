/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:00:39 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/27 22:50:55 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*get_brace_str(int shell_var_brace, char *line, t_prompt *prompt)
{
	char *tmp;
	char *str;

	if (shell_var_brace > 0)
	{
		if (!(tmp = ft_strsub(line, 2, ft_strlen(line))))
			return (NULL);
		str = ft_strjoin("$", tmp);
		free(tmp);
		prompt->select.cursor_left_len -= 2;
		return (str);
	}
	prompt->select.cursor_left_len -= 1;
	return (ft_strdup(line));
}

int		first_word(char *line, size_t i, size_t max, int first)
{
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] && i < max)
		first = 0;
	while (line[i] && i < max)
	{
		if (line[i] == '|' || line[i] == '&' || line[i] == ';')
		{
			i++;
			return (first_word(line, i + 2, max, 1));
		}
		i++;
	}
	return (first);
}

int		get_path(t_sh *shell, char **line, char **path)
{
	char	*tmp;
	char	*home;
	int		i;

	tmp = NULL;
	if (**line == '~' && get_var(shell, "HOME", &home) == SH_SUCCESS)
	{
		*line = ft_strsrepl(*line, "~", home);
		tmp = *line;
	}
	if (ft_strchr(*line, '/'))
	{
		i = ft_strrchr(*line, '/') - *line;
		*path = ft_strsub(*line, 0, i + 1);
		*line = ft_strdup(*line + i + 1);
	}
	else
	{
		*path = ft_strdup(".");
		*line = ft_strdup(*line);
	}
	if (tmp)
		free(tmp);
	return ((*path && *line) ? SH_SUCCESS : SH_ERR_MALLOC);
}

int		get_cursor_word_len(char *line, t_prompt *prompt, int i, int j)
{
	prompt->select.cursor_left_len = j - i;
	prompt->select.cursor_left_len = i == 0 ? prompt->select.cursor_left_len + 1
		: prompt->select.cursor_left_len;
	i = j;
	while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '\n')
		j++;
	prompt->select.cursor_right_len = j - i;
	return (SH_SUCCESS);
}

char	*get_cursor_word(char *line, t_prompt *prompt)
{
	int		i;
	int		j;
	char	*word;
	char	*tmp;

	i = (int)prompt->buffer_index;
	j = i;
	while (i > 0)
	{
		if (line[i - 1] == ' ' || line[i - 1] == '\t' || line[i - 1] == '\n')
			break ;
		i--;
	}
	tmp = ft_strsub(line, i, (j - i));
	if (!tmp || !(word = ft_strtrim(tmp)))
		return (NULL);
	free(tmp);
	get_cursor_word_len(line, prompt, i, j);
	return (word);
}
