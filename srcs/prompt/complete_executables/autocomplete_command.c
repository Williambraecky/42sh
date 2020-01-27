/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzaga <mpizzaga@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:57:42 by mpizzaga          #+#    #+#             */
/*   Updated: 2020/01/27 22:34:52 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int		complete_shell_var(char *line, t_vec *poss, t_sh *shell,
		t_prompt *prompt)
{
	char	*key;
	size_t	i;
	char	*str;

	prompt->select.shell_var_brace = line[1] == '{' ? 1 : 0;
	if (!(str = get_brace_str(prompt->select.shell_var_brace, line, prompt)))
		return (SH_ERR_MALLOC);
	i = 0;
	while (i < shell->vars->max_size)
	{
		if (shell->vars->nodes[i].is_used)
		{
			key = shell->vars->nodes[i].key;
			if (ft_strstartswith(key, str + 1))
				if (posscpush(poss, key, ft_strlen(key) + 1))
				{
					free(str);
					return (SH_ERR_MALLOC);
				}
		}
		i++;
	}
	free(str);
	return (SH_SUCCESS);
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
			if (posscpush(poss, sd->d_name, ft_strlen(sd->d_name) + 1))
			{
				closedir(dir);
				return (SH_ERR_NOEXIST);
			}
	}
	closedir(dir);
	return (SH_SUCCESS);
}

int		complete_files(t_sh *shell, t_prompt *prompt, char *line, t_vec *poss)
{
	int		ret;
	char	*path;
	char	*tmp;

	tmp = line;
	if (get_path(shell, &line, &path) == SH_ERR_MALLOC)
		return (SH_ERR_MALLOC);
	free(tmp);
	prompt->select.cursor_left_len = ft_wstrlen(line);
	if ((ret = get_files(line, path, poss)) != SH_SUCCESS)
	{
		free(path);
		free(line);
		return (ret);
	}
	free(path);
	free(line);
	prompt->select.file_complete = 1;
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
	if (!first_word(line, 0, prompt->buffer_index, 1))
		return (complete_files(shell, prompt, to_complete, poss));
	if (!ft_strequ(to_complete, ".") && !ft_strequ(to_complete, ".."))
	{
		complete_command(shell, to_complete, poss);
		if (poss->size != 0)
		{
			free(to_complete);
			return (SH_SUCCESS);
		}
	}
	if (poss->size == 0)
		complete_files(shell, prompt, to_complete, poss);
	return (SH_SUCCESS);
}
