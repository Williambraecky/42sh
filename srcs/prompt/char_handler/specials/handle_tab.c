/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:55:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/08 17:41:42 by mpizzaga         ###   ########.fr       */
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

static int	one_poss_only(char *line, t_vec *poss, t_sh *shell, t_prompt *prompt)
{
	char	*complete_command;
	size_t	i;

	i = 0;
	complete_command = (char *)ft_vecget(poss, 0);
	while (complete_command[i] && complete_command[i] == line[i]) //TODO: Invalid when not completing beginning of input
		i++;
	ft_vecfree(poss);
	default_char_handler(prompt, complete_command + i, shell);
	free(complete_command);
	default_char_handler(prompt, " ", shell);
	return (RET_CONT);
}

/*
** NOTE: first tab creates poss vector; second tab goes into select mode
*/

int			handle_tab(t_prompt *prompt, char *buffer, t_sh *shell)
{
	char	*line;
	t_vec	poss;
//	size_t	i;
	(void)buffer;

	line = prompt->buffer.buffer;
	if (prompt->select_mode == 1)
	{
		prompt->select.selected = 0;
		prompt->select_mode = 2;
		select_render(prompt, &prompt->select);
		//TODO: render again
		//NOTE: we already processed the completion just need to enter select mode
		//NOTE: this also implies that we free poss correctly all the time
		return (RET_CONT);
	}
	if(ft_vecinit(&poss))
		return (SH_ERR_MALLOC);
	autocomplete_command(line, shell, &poss, prompt);
	if (poss.size == 0)
	{
		ft_vecfree(&poss);
		return (RET_CONT);
	}
	if (poss.size == 1)
		return (one_poss_only(line, &poss, shell, prompt));
//	i = 0;
//	while (i < poss.size)
//	{
//		ft_strsreplall((char *)ft_vecget(&poss, i), " ", "\\ ");
//		i++;
//	}
	ft_vecsort(&poss, ft_strcmp);
	ft_select(shell, &poss, prompt);
	return (RET_CONT);
}
