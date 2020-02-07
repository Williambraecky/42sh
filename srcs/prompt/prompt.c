/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:45:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 20:15:19 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

extern sig_atomic_t	g_winchange;
extern sig_atomic_t	g_sigint;

static void	recalc_cursor(t_prompt *prompt)
{
	size_t	written;

	g_winchange = 0;
	if (!prompt->valid_size)
		return ;
	gettermsize(&prompt->winsize);
	written = prompt->prompt_len;
	prompt->prompt_pos = calc_prompt_pos(prompt);
	if (prompt->buffer.buffer)
		written += prompt->char_index;
	prompt->cursor_pos = calc_cursor_pos(prompt, written);
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
	ret = SH_SUCCESS;
	while (!prompt->done)
	{
		buffer = 0;
		if ((j = read(0, &buffer, 1)) == -1)
		{
			ret = g_sigint ? SH_ERR_SIGINT : SH_ERR_READ;
			break ;
		}
		j += read(0, (char *)(&buffer) + 1, wcharlen(buffer) - 1);
		if (g_winchange)
			recalc_cursor(prompt);
		if ((ret = handle_new_char(prompt, (char*)&buffer, shell))
			!= SH_SUCCESS)
			break ;
	}
	move_goto(prompt, prompt->max_pos);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	move_cursor((t_pos){.x = 0, .y = 1});
	return (ret);
}

/*
** NOTE: Basic non interactive prompt for file reading; No prompt printing
*/

static int	basic_prompt(t_sh *shell, t_prompt *prompt)
{
	char	buff;
	int		ret;

	(void)shell;
	buff = 0;
	while (buff != '\n' && (ret = read(0, &buff, 1)) == 1)
		if ((ret = buff_nappend(&prompt->buffer, &buff, 1)) != SH_SUCCESS)
			return (ret);
	if (ret == 0 && !prompt->buffer.size)
		return (SH_READ_DONE);
	else if (ret == -1)
		return (SH_ERR_MALLOC);
	return (SH_SUCCESS);
}

int			handle_prompt(t_sh *shell, char *prompt_str, char **result)
{
	t_prompt	prompt;
	int			err_code;

	ft_memset(&prompt, 0, sizeof(prompt));
	g_sigint = 0;
	if ((err_code = gen_prompt(shell, prompt_str, &prompt)) != SH_SUCCESS)
		return (err_code);
	if (shell->interactive_mode)
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
	free_prompt(shell, &prompt);
	return (err_code);
}
