/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shift_arrows.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 01:26:19 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 20:16:10 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static void		prev_word(t_prompt *prompt)
{
	char	*buff;
	size_t	i;
	int		j;

	buff = prompt->buffer.buffer;
	i = prompt->buffer_index;
	j = prompt->char_index;
	while (j > 0)
	{
		if (ft_isalnum(*ft_wstrindex(buff, j - 1)))
			break ;
		j--;
	}
	while (j > 0)
	{
		if (!ft_isalnum(*ft_wstrindex(buff, j - 1)))
			break ;
		j--;
	}
	i = ft_wstrindex(buff, j) - buff;
	if (i == prompt->buffer_index)
		return ;
	prompt->buffer_index = i;
	prompt->char_index = j;
	move_goto(prompt, calc_cursor_pos(prompt, j));
}

static void		skip_word(t_prompt *prompt)
{
	char	*buff;
	size_t	i;
	size_t	j;

	buff = prompt->buffer.buffer;
	i = prompt->buffer_index;
	j = prompt->char_index;
	while (buff[i] && ft_isalnum(buff[i]))
	{
		i += wcharlen(buff[i]);
		j++;
	}
	while (buff[i] && !ft_isalnum(buff[i]))
	{
		i += wcharlen(buff[i]);
		j++;
	}
	if (i == prompt->buffer_index)
		return ;
	prompt->buffer_index = i;
	prompt->char_index = j;
	move_goto(prompt, calc_cursor_pos(prompt, j));
}

int				handle_shift_arrows(t_prompt *prompt, char *buffer, t_sh *shell)
{
	(void)shell;
	if (buffer[3] == 'A')
		prev_line(prompt);
	else if (buffer[3] == 'B')
		next_line(prompt);
	else
		prompt->nl_offset = -1;
	if (buffer[3] == 'C')
		skip_word(prompt);
	else if (buffer[3] == 'D')
		prev_word(prompt);
	return (SH_SUCCESS);
}
