/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:00:39 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/22 22:10:43 by wbraeckm         ###   ########.fr       */
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

int		first_word(char *line, size_t i, int first)
{
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i])
		first = 0;
	while (line[i])
	{
		if (line[i] == '|' || line[i] == '&' || line[i] == ';')
		{
			i++;
			return (first_word(line, i + 2, 1));
		}
		i++;
	}
	return (first);
}

int		get_path(t_sh *shell, char **line, char **path)
{
	int		i;

	if (**line == '~' && has_env(shell, "HOME"))
	{
		*line = ft_strdup(*((*line) + 1) == '/' ? (*line) + 2 : (*line) + 1);
		return (get_env_clone(shell, "HOME", path));
	}
	i = ft_strlen(*line) - 1;
	if (ft_strchr(*line, '/'))
	{
		while (i > 0 && line[0][i] != '/')
			i--;
		*path = ft_strsub(*line, 0, i + 1);
		*line = ft_strdup(*line + i + 1);
	}
	else
	{
		*path = ft_strdup(".");
		*line = ft_strdup(*line);
	}
	if (!*path || !*line)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

int		get_cursor_word_len(char *line, t_prompt *prompt, int i, int j)
{
	prompt->select.cursor_left_len = j - i;
	prompt->select.cursor_left_len = i == 0 ? prompt->select.cursor_left_len + 1
		: prompt->select.cursor_left_len;
	i = j;
	while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '\n')
		j++;
	prompt->select.cursor_right_len = j - i - 1;
//	ft_printf("\nright = %d -- left = %d\n", prompt->select.cursor_right_len, prompt->select.cursor_left_len);
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
	while (i > 0 && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i--;
	tmp = ft_strsub(line, i, (j - i) + 1);
	if (!tmp || !(word = ft_strtrim(tmp)))
		return (NULL);
	free(tmp);
	get_cursor_word_len(line, prompt, i, j);
	return (word);
}
