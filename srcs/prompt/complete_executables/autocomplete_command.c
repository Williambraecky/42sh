/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:07:28 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/12/13 19:33:39 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

//NORMER
//FINIR matching_bin_builtin_currdir()
//COMPLETER LA LISTE DE BUILTIN
//TESTER
//REMETTRE LE SH.C ET LE SH.H AU PROPRE

char		*builtin_list[] =
{
	"echo", "cd", "test"
};

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
	int i;
	int j;
	char *last_word = NULL;

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

char		**autocomplete_poss(char *path, char *start)
{
	DIR				*dir;
	struct dirent	*sd;
	char			**poss = NULL;

	ft_printf("autocomplete_poss = path = %s -- start = %s\n", path, start);
	dir = opendir(path);
	if (dir == NULL)
	{
		ft_printf("error while opening the dir\n");
		return (NULL);
	}
	while ((sd = readdir(dir)) != NULL)
	{
		if (start && ft_strstartswith(sd->d_name, start))
		{
			if ((ft_strequ(sd->d_name, ".") || ft_strequ(sd->d_name, ".."))
			&& ft_strequ("", start))
				continue;
			ft_printf("\n%s", sd->d_name);//temporaire ==> add to poss
		}
	}
	return (poss);
}

int			get_path_index(char *last_word)
{
	ft_printf("get_path_index\n");
	int		i;

	i = ft_strlen(last_word) - 1;
	while (last_word[i] != '/')
		i--;
	return (i);
}

char		**autocomplete_command(char *line, t_sh *shell)
{
	char	*last_word;
	int		space;
	char	*path;
	int		path_index;
	char	**poss;

	(void)shell; //temporaire
	if (count_words(line) == 0)
		return (NULL); //temporaire
//		return (matching_bin_builtin_currdir(t_sh->env, builtin_list, ""));
	last_word = get_last_word(line, &space);
	if (space)
		return (autocomplete_poss(".", ""));
	if (ft_strstartswith(last_word, "/") || ft_strstartswith(last_word, "../"))
	{
		path_index = get_path_index(last_word);
		if (!(path = ft_strsub(last_word, 0, path_index + 1)))
			ft_printf("MALLOC ERROR WHILE GETTING PATH\n");
		last_word = last_word + path_index + 1;
		printf("last_word = %s -- path = %s\n", last_word, path);
		poss = autocomplete_poss(path, last_word);
		free(path);
		return (poss);
	}
//	else		//else necessaire!!!
//		return (matching_bin_builtin_currdir(t_sh->env, builtin_list, last_word));
	return (NULL);
}
