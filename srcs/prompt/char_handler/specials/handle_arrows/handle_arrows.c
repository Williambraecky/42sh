/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:53:09 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/19 01:26:30 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** NOTE: up = 1 down = 2
*/

static void	prepare_query(t_prompt *prompt)
{
	buff_clear(&prompt->buffer);
	move_goto(prompt, prompt->prompt_pos);
	prompt->char_index = 0;
	prompt->buffer_index = 0;
}

static int	handle_query(t_prompt *prompt, int direction, t_sh *shell)
{
	char	*queried;

	if (!prompt->querying)
	{
		if (direction == 2)
			return (SH_SUCCESS);
		if (!(prompt->query.query =
			ft_strndup(prompt->buffer.buffer, prompt->buffer_index)))
			return (SH_ERR_MALLOC);
		if (!(prompt->query.orig = ft_strdup(prompt->buffer.buffer)))
			return (SH_ERR_MALLOC);
		prompt->query.curr_index = shell->history.size;
		prompt->querying = 1;
	}
	if (direction == 1)
		queried = hquery_prev(shell, &prompt->query);
	else
		queried = hquery_next(shell, &prompt->query);
	if (!queried)
		return (SH_ERR_MALLOC);
	prepare_query(prompt);
	return (default_char_handler(prompt, queried, shell));
}

int			handle_arrows(t_prompt *prompt, char *buffer, t_sh *shell)
{
	if (buffer[2] == 'A')
		return (handle_query(prompt, 1, shell));
	else if (buffer[2] == 'B')
		return (handle_query(prompt, 2, shell));
	else if (buffer[2] == 'C')
		move_right(prompt);
	else if (buffer[2] == 'D')
		move_left(prompt);
	else if (buffer[2] == 'H' && prompt->char_index != 0)
	{
		prompt->buffer_index = 0;
		prompt->char_index = 0;
		move_goto(prompt, prompt->prompt_pos);
	}
	else if (buffer[2] == 'F')
	{
		prompt->char_index = ft_wstrlen(prompt->buffer.buffer);
		prompt->buffer_index = ft_wstrindex(prompt->buffer.buffer,
			prompt->char_index) - prompt->buffer.buffer;
		move_goto(prompt, prompt->max_pos);
	}
	return (SH_SUCCESS);
}
