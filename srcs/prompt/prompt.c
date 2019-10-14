/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:45:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/14 17:57:09 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

/*
** NOTE: Interactive prompt; Prompt gets printed here
*/

static char	*interactive_prompt(t_sh *shell, t_prompt *prompt)
{
	int		buffer;
	ssize_t	j;

	(void)shell;
	if (prompt->valid_pos && prompt->cursor_pos.x != 1)
	{
		ft_dprintf(0, "{invert}{bold}%%{eoc}\n");
		prompt->cursor_pos.x = 1;
		prompt->cursor_pos.y++;
	}
	ft_putstr_fd(prompt->prompt, 0);
	prompt->cursor_pos.x += ft_strlen(prompt->prompt);
	j = read(0, &buffer, 1);
	j += read(0, (char *)(&buffer) + 1, wcharlen(buffer) - 1);
	// 1110 4 char 110 3 char 10 2 char
	write(0, &buffer, j);
	free_prompt(prompt);
	return (NULL);
}

/*
** NOTE: Basic non interactive prompt for file reading; No prompt printing
*/

static char	*basic_prompt(t_sh *shell, t_prompt *prompt)
{
	(void)shell;
	(void)prompt;
	return (NULL);
}

char		*handle_prompt(t_sh *shell)
{
	t_prompt	prompt;

	ft_memset(&prompt, 0, sizeof(prompt));
	gen_prompt(shell, &prompt);
	if (shell->prompt_mode)
		return (interactive_prompt(shell, &prompt));
	return (basic_prompt(shell, &prompt));
}
