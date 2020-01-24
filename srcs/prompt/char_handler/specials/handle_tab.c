/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:55:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/24 23:50:48 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int			select_handle_tab(t_prompt *prompt, char *buffer, t_sh *shell)
{
	t_select *select;

	(void)buffer;
	(void)shell;
	select = &prompt->select;
	select->selected = (select->selected == select->nb_elem - 1) ? 0
		: select->selected + 1;
	select_render(prompt, select);
	return (SH_SUCCESS);
}

static int	one_poss_only(t_vec *poss, t_prompt *prompt)
{
	char	*str;
	size_t	i;

	str = (char *)ft_vecget(poss, 0);
	i = (int)prompt->buffer_index - 1;
	while (prompt->select.cursor_right_len > 0)
	{
		move_right(prompt);
		handle_backspace(prompt, NULL, NULL);
		prompt->select.cursor_right_len--;
	}
	while (prompt->select.cursor_left_len && prompt->buffer.buffer[i] != '/')
	{
		handle_backspace(prompt, NULL, NULL);
		prompt->select.cursor_left_len--;
		i--;
	}
	default_char_handler(prompt, str, NULL);
	if (prompt->select.shell_var_brace)
		default_char_handler(prompt, "}", NULL);
	else
		default_char_handler(prompt, is_dir(str) ? "/" : " ", NULL);
	ft_vecdestroy(poss, default_vec_destroy_function);
	return (SH_SUCCESS);
}

/*
** NOTE: first tab creates poss vector; second tab goes into select mode
*/

static int	replace_space_poss(t_vec *poss)
{
	void	*tmp;
	size_t	i;
	char	*space_free_str;

	i = 0;
	while (i < poss->size)
	{
		tmp = ft_vecget(poss, i);
		if (ft_strchr((char*)tmp, ' '))
		{
			if (!(space_free_str = ft_strsreplall((char*)tmp, " ", "\\ ")))
				return (SH_ERR_MALLOC);
			if (ft_vecset(poss, (char *)space_free_str, i))
				return (SH_ERR_MALLOC);
			free(tmp);
		}
		i++;
	}
	return (SH_SUCCESS);
}

static int	select_mode_one(t_prompt *prompt)
{
	prompt->select.selected = 0;
	prompt->select_mode = 2;
	select_render(prompt, &prompt->select);
	return (SH_SUCCESS);
}

int			handle_tab(t_prompt *prompt, char *buffer, t_sh *shell)
{
	char	*line;
	t_vec	poss;

	(void)buffer;
	line = prompt->buffer.buffer;
	if (prompt->select_mode == 1)
		return (select_mode_one(prompt));
	if (ft_vecinit(&poss))
		return (SH_ERR_MALLOC);
	prompt->select.shell_var_brace = 0;
	prompt->select.file_complete = 0;
	autocomplete_command(line, shell, &poss, prompt);
	if (replace_space_poss(&poss) == SH_ERR_MALLOC)
		return (SH_ERR_MALLOC);
	if (poss.size == 0)
	{
		ring_bell();
		ft_vecfree(&poss);
		return (SH_SUCCESS);
	}
	if (poss.size == 1)
		return (one_poss_only(&poss, prompt));
	ft_vecsort(&poss, ft_strcmp);
	ft_select(shell, &poss, prompt);
	return (SH_SUCCESS);
}
