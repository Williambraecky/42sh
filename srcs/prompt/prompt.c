/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:45:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/15 19:08:36 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static int	add_to_buffer(t_prompt *prompt, char *buffer)
{
	char	*result;

	if (!(result =
		ft_strinsert(prompt->buffer, buffer, prompt->buffer_index)))
	{
		ft_strdel(&prompt->buffer);
		return (1);
	}
	prompt->buffer_index += wcharlen(*buffer);
	prompt->char_index++;
	ft_strdel(&prompt->buffer);
	prompt->buffer = result;
	return (0);
}

static void	print_prompt(t_sh *shell, t_prompt *prompt)
{
	if (prompt->valid_pos && prompt->cursor_pos.x != 1)
	{
		ft_dprintf(0, "{invert}{bold}%%{eoc}\n");
		prompt->cursor_pos.x = 1;
		prompt->cursor_pos.y++;
	}
	ft_putstr_fd(prompt->prompt, 0);
	if (prompt->valid_pos)
	{
		get_cursor_pos(shell, &prompt->cursor_pos.x, &prompt->cursor_pos.y);
		prompt->prompt_len = prompt->cursor_pos.x;
	}
}

/*
** NOTE: Interactive prompt; Prompt gets printed here
*/

static int	interactive_prompt(t_sh *shell, t_prompt *prompt)
{
	long	buffer;
	ssize_t	j;

	print_prompt(shell, prompt);
	while (19)
	{
		buffer = 0;
		j = read(0, &buffer, 1);
		j += read(0, (char *)(&buffer) + 1, wcharlen(buffer) - 1);
		if (buffer == '\n')
			break ;
		add_to_buffer(prompt, (char *)&buffer);
		write(0, &buffer, wcharlen(buffer));
	}
	free_prompt(prompt);
	return (0);
}

/*
** NOTE: Basic non interactive prompt for file reading; No prompt printing
*/

static int	basic_prompt(t_sh *shell, t_prompt *prompt)
{
	(void)shell;
	(void)prompt;
	return (0);
}

int			handle_prompt(t_sh *shell, char **result)
{
	t_prompt	prompt;
	int			err_code;

	ft_memset(&prompt, 0, sizeof(prompt));
	if ((err_code = gen_prompt(shell, &prompt)))
		return (err_code);
	if (shell->prompt_mode)
		err_code = interactive_prompt(shell, &prompt);
	else
		err_code = basic_prompt(shell, &prompt);
	if (!err_code)
		*result = prompt.buffer;
	return (err_code);
}
