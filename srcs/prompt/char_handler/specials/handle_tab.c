/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:55:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/14 16:37:23 by mpizzaga         ###   ########.fr       */
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
	return (RET_CONT);
}

static int	one_poss_only(char *line, t_vec *poss, t_sh *shell,
		t_prompt *prompt)
{
	char	*str;
	size_t	i;
	int		command_complete;

	(void)shell;
	(void)line;
	str = (char *)ft_vecget(poss, 0);
	i = (int)prompt->buffer_index - 1;
	command_complete = prompt->select.command_complete ? 0 : 1;
	while (prompt->select.cursor_right_len > 0)
	{
		move_right(prompt);
		handle_backspace(prompt, NULL, NULL);
		prompt->select.cursor_right_len--;
	}
	while (prompt->select.cursor_left_len + command_complete
			&& prompt->buffer.buffer[i] != '/')
	{
		handle_backspace(prompt, NULL, NULL);
		prompt->select.cursor_left_len--;
		i--;
	}
	default_char_handler(prompt, str, NULL);
	default_char_handler(prompt, " ", NULL);
	return (RET_CONT);
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

int			select_mode_one(t_prompt *prompt)
{
	prompt->select.selected = 0;
	prompt->select_mode = 2;
	select_render(prompt, &prompt->select);
	//TODO: render again
	//NOTE: we already processed the completion just need to enter select mode
	//NOTE: this also implies that we free poss correctly all the time
	return (RET_CONT);
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
	prompt->select.command_complete = 0;
	autocomplete_command(line, shell, &poss, prompt);
	if (replace_space_poss(&poss) == SH_ERR_MALLOC)
		return (SH_ERR_MALLOC);
	if (poss.size == 0)
	{
		ft_vecfree(&poss);
		return (RET_CONT);
	}
	if (poss.size == 1)
		return (one_poss_only(line, &poss, shell, prompt));
	ft_vecsort(&poss, ft_strcmp);
	ft_select(shell, &poss, prompt);
	return (RET_CONT);
}
