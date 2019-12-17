/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:00:39 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/12/17 18:39:36 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int			count_words(char *line)
{
	int words;
	int i;

	words = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i])
			words++;
		while (line[i] != ' ' && line[i])
			i++;
		i++;
	}
	return (words);
}

char		*get_last_word(char *line, int *space)
{
	int		i;
	int		j;
	char	*last_word;

	i = ft_strlen(line) - 1;
	*space = line[i] == ' ' ? 1 : 0;
	while (line[i] == ' ')
		i--;
	j = i;
	while (j >= 0 && line[j] != ' ')
		j--;
	last_word = line + j + 1;
	return (last_word);
}

int			is_reset_token(char *last_word)
{
	if (ft_strequ(last_word, "|") || ft_strequ(last_word, ";") ||
		ft_strequ(last_word, "&&") || ft_strequ(last_word, "||") ||
		ft_strequ(last_word, "&"))
		return (1);
	return (0);
}

int			is_redirection(char *last_word)
{
	if (ft_strequ(last_word, ">") || ft_strequ(last_word, "<"))
		return (1);
	return (0);
}

int			get_path_last_word(char **last_word, char **path)
{
	int		i;

	i = ft_strlen(*last_word) - 1;
	while (last_word[0][i] != '/')
		i--;
	if (!(*path = ft_strsub(*last_word, 0, i + 1)))
		return (SH_ERR_MALLOC);
	*last_word = *last_word + i + 1;
	return (SH_SUCCESS);
}
