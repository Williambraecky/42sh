/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:55:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/06 19:37:52 by mpizzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int	one_poss_only(char *line, t_vec *poss, t_sh *shell, t_prompt *prompt)
{
	char	*complete_command;
	size_t	i;
//	long	buf;

	i = 0;
	complete_command = (char *)ft_vecget(poss, 0);
	while (complete_command[i] == line[i])
		i++;
	complete_command += i;
	default_char_handler(prompt, complete_command, shell);
	//adjust cursor and add a space
	return (RET_CONT);
}

int			handle_tab(t_prompt *prompt, char *buffer, t_sh *shell)
{
	char	*line;
	t_vec	poss;
	(void)buffer;

	line = prompt->buffer.buffer;
	if(ft_vecinit(&poss))
		return (SH_ERR_MALLOC);
	autocomplete_command(line, shell, &poss);
	if (poss.size == 0)
		return (RET_CONT);
	if (poss.size == 1)
		return (one_poss_only(line, &poss, shell, prompt));
	ft_vecsort(&poss, ft_strcmp);
	ft_select(shell, &poss, prompt);
//	free_vec();
	return (RET_CONT);
}
