/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:57:42 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/14 16:27:09 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int		get_internals(char *str, t_vec *poss, t_map *internals)
{
	char	*key;
	size_t	i;

	i = 0;
	while (i < internals->max_size)
	{
		if (internals->nodes[i].is_used)
		{
			key = internals->nodes[i].key;
			if (ft_strstartswith(key, str + 1))
				if (ft_veccpush(poss, key, ft_strlen(key) + 1))
					return (SH_ERR_NOEXIST);
		}
		i++;
	}
	free(str);
	return (SH_SUCCESS);
}

int		complete_shell_var(char *line, t_vec *poss, t_sh *shell,
		t_prompt *prompt)
{
	t_map	*env;
	t_map	*internals;
	char	*key;
	size_t	i;
	char	*str;

	prompt->select.shell_var_brace = line[1] == '{' ? 1 : 0;
	if (!(str = get_brace_str(prompt->select.shell_var_brace, line, prompt)))
		return (SH_ERR_MALLOC);
	env = shell->env;
	internals = shell->internals;
	i = 0;
	while (i < env->max_size)
	{
		if (env->nodes[i].is_used)
		{
			key = env->nodes[i].key;
			if (ft_strstartswith(key, str + 1))
				if (ft_veccpush(poss, key, ft_strlen(key) + 1))
					return (SH_ERR_NOEXIST);
		}
		i++;
	}
	return (get_internals(str, poss, internals));
}

int		get_files(char *line, char *path, t_vec *poss)
{
	DIR				*dir;
	struct dirent	*sd;

	if (!(dir = opendir(path)))
		return (SH_ERR_OPEN_DIR);
	while ((sd = readdir(dir)) != NULL)
	{
		if ((ft_strequ(sd->d_name, ".") || ft_strequ(sd->d_name, "..")) &&
			(!ft_strequ(line, ".") && !ft_strequ(line, "..")))
			continue;
		if (ft_strstartswith(sd->d_name, line))
			if (ft_veccpush(poss, sd->d_name, ft_strlen(sd->d_name) + 1))
			{
				closedir(dir);
				return (SH_ERR_NOEXIST);
			}
	}
	closedir(dir);
	return (SH_SUCCESS);
}

int		complete_files(t_prompt *prompt, char *line, t_vec *poss)
{
	int		ret;
	char	*path;
	char	*tmp;

	tmp = line;
	if (get_path(&line, &path) == SH_ERR_MALLOC)
		return (SH_ERR_MALLOC);
	free(tmp);
	prompt->select.cursor_left_len = ft_strlen(line) - 1;
	if ((ret = get_files(line, path, poss)) > 0)
		return (ret);
	free(path);
	free(line);
	return (SH_SUCCESS);
}

int		autocomplete_command(char *line, t_sh *shell, t_vec *poss,
t_prompt *prompt)
{
	char	*to_complete;

	if (!(to_complete = get_cursor_word(line, prompt)))
		return (SH_ERR_MALLOC);
	if (to_complete[0] == '$')
	{
		if (complete_shell_var(to_complete, poss, shell, prompt))
			return (SH_ERR_MALLOC);
		free(to_complete);
		return (SH_SUCCESS);
	}
	if (!first_word(line, 0, 1))
		return (complete_files(prompt, to_complete, poss));
	if (!ft_strequ(to_complete, ".") && !ft_strequ(to_complete, ".."))
	{
		complete_command(shell, to_complete, poss, prompt);
		if (poss->size != 0)
		{
			free(to_complete);
			return (SH_SUCCESS);
		}
	}
	if (poss->size == 0)
		complete_files(prompt, to_complete, poss);
	return (SH_SUCCESS);
}
