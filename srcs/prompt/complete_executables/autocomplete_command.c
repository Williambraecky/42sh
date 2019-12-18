/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:57:42 by mpizzaga          #+#    #+#             */
/*   Updated: 2019/12/18 17:34:20 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int			autocomplete_poss(char *path, char *start, t_vec *poss)
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
			if (ft_veccpush(poss, sd->d_name, ft_strlen(sd->d_name)))
				return (SH_ERR_NOEXIST);
		}
	}
	closedir(dir);
	return (SH_SUCCESS);
}

int			get_matching_env(t_map *env, char *last_word, t_vec *poss)
{
	char	*start;
	size_t	i;
	char	*key;

	start = last_word + 1;
	i = 0;
	while (i < env->max_size)
	{
		if (env->nodes[i].is_used)
		{
			key = env->nodes[i].key;
			if (ft_strstartswith(key, start))
				if (ft_veccpush(poss, key, ft_strlen(key)))
					return (SH_ERR_NOEXIST);
		}
		i++;
	}
	return (SH_SUCCESS);
}

int			autocomplete_command(char *line, t_sh *shell, t_vec *poss)
{
	char	*last_word;
	int		space;
	char	*path;
	int		ret;

	if (count_words(line) == 0)
		return (match_bin_built(shell, "", poss));
	last_word = get_last_word(line, &space);
	if ((space && !is_reset_token(last_word)) || is_redirection(last_word))
		return (autocomplete_poss(".", "", poss));
	if (ft_strstartswith(last_word, "$"))
		return (get_matching_env(shell->env, last_word, poss));
	if (ft_strstartswith(last_word, "/") || ft_strstartswith(last_word, "../")
	|| ft_strstartswith(last_word, "./"))
	{
		if ((ret = get_path_last_word(&last_word, &path)) != SH_SUCCESS)
			return (ret);
		ret = autocomplete_poss(path, last_word, poss);
		free(path);
		return (ret);
	}
	else if (is_reset_token(last_word))
		return (match_bin_built(shell, last_word, poss));
	return (SH_SUCCESS);
}
