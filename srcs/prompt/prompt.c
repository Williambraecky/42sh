/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:45:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/14 00:35:04 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

extern sig_atomic_t	g_winchange;
extern sig_atomic_t	g_sigint;

/*
** TODO: we cannot just recalculate cursor position as it doesn't always follow
**  window changement (cursor at end of text or not) so we need something else
**  or simply reprint the prompt aswell before reprint buffer
*/

static void	recalc_cursor(t_prompt *prompt)
{
	size_t	written;

	g_winchange = 0;
	if (!prompt->valid_size)
		return ;
	gettermsize(&prompt->winsize);
	written = prompt->prompt_len;
	prompt->prompt_pos = new_calc(prompt, written);
	prompt->from_line = prompt->prompt_pos.y;
	if (prompt->buffer.buffer)
		written += prompt->char_index;
	prompt->cursor_pos = new_calc(prompt, written);
	reprint_everything(prompt);
}

static void	print_prompt(t_sh *shell, t_prompt *prompt)
{
	(void)shell;
	if (prompt->valid_pos && prompt->cursor_pos.x != 1)
		ft_dprintf(0, "{invert}{bold}%%{eoc}\n");
	ft_putstr_fd(prompt->prompt, 0);
	prompt->prompt_len = strlen_nocolor(prompt->prompt);
	recalc_cursor(prompt);
}

/*
** NOTE: Interactive prompt; Prompt gets printed here
*/

static int	interactive_prompt(t_sh *shell, t_prompt *prompt)
{
	int		ret;
	long	buffer;
	ssize_t	j;

	print_prompt(shell, prompt);
	ret = 0;
	while (19)
	{
		buffer = 0;
		j = read(0, &buffer, 1);
		if (j == -1)
			return (SH_ERR_SIGINT);
		j += read(0, (char *)(&buffer) + 1, wcharlen(buffer) - 1);
		if (g_winchange)
			recalc_cursor(prompt);
		ret = handle_new_char(prompt, (char*)&buffer, shell);
		if (ret & RET_REPRINT)
			reprint_buffer(prompt);
		if (!(ret & RET_CONT))
			break ;
	}
	move_goto(prompt, prompt->max_pos);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	move_cursor((t_pos){.x = 0, .y = 1});
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

int			handle_prompt(t_sh *shell, char *prompt_str, char **result)
{
	t_prompt	prompt;
	int			err_code;

	ft_memset(&prompt, 0, sizeof(prompt));
	g_sigint = 0;
	tcsetattr(SH_IN, TCSADRAIN, &shell->current_termios);
	if ((err_code = gen_prompt(shell, prompt_str, &prompt)) != SH_SUCCESS)
		return (err_code);
	if (shell->prompt_mode)
		err_code = interactive_prompt(shell, &prompt);
	else
		err_code = basic_prompt(shell, &prompt);
	if (err_code == SH_SUCCESS)
		*result = prompt.buffer.buffer;
	else
	{
		*result = NULL;
		free(prompt.buffer.buffer);
	}
	tcsetattr(SH_IN, TCSADRAIN, &shell->old_termios);
	free_prompt(&prompt);
	return (err_code);
}
