/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 03:09:02 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/19 16:06:01 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static size_t	offset_newline(t_prompt *prompt, char *str, size_t index)
{
	size_t	j;

	if (prompt->nl_offset != -1)
		return ((size_t)prompt->nl_offset);
	j = index;
	if (j == 0)
		return (0);
	while (j)
	{
		if (j == 0 || *ft_wstrindex(str, j - 1) == '\n')
			break ;
		j--;
	}
	return (index - j);
}

static size_t	next_newline(char *str, size_t index)
{
	size_t	i;
	size_t	j;

	j = ft_wstrindex(str, index) - str;
	i = index;
	while (str[j])
	{
		if (str[j] == '\n')
			break ;
		j += wcharlen(str[j]);
		i++;
	}
	return (i - index);
}

static int		prev_newline(char *str, size_t index)
{
	size_t		j;

	j = index;
	while (j)
	{
		if (j == 0 || *ft_wstrindex(str, j - 1) == '\n')
			break ;
		j--;
	}
	if (j == 0)
		return (-1);
	j--;
	while (j)
	{
		if (j == 0 || *ft_wstrindex(str, j - 1) == '\n')
			break ;
		j--;
	}
	return (j);
}

void			prev_line(t_prompt *prompt)
{
	char		*str;
	char		*tmp;
	size_t		nl_offset;
	size_t		i;
	int			prev_nl;

	str = prompt->buffer.buffer;
	prev_nl = prev_newline(str, prompt->char_index);
	if (prev_nl == -1)
		return ;
	nl_offset = offset_newline(prompt, str, prompt->char_index);
	prompt->nl_offset = (int)nl_offset;
	i = (size_t)prev_nl;
	while (nl_offset--)
	{
		tmp = ft_wstrindex(str, i);
		if (*tmp == '\n' || *tmp == '\0')
			break ;
		i++;
	}
	prompt->char_index = i;
	prompt->buffer_index = ft_wstrindex(str, prompt->char_index) - str;
	move_goto(prompt, calc_cursor_pos(prompt, prompt->char_index));
}

void			next_line(t_prompt *prompt)
{
	char		*str;
	char		*tmp;
	size_t		nl_offset;
	size_t		i;
	size_t		next_nl;

	str = prompt->buffer.buffer;
	next_nl = next_newline(str, prompt->char_index);
	if (str[next_nl + prompt->char_index] == '\0')
		return ;
	nl_offset = offset_newline(prompt, str, prompt->char_index);
	prompt->nl_offset = (int)nl_offset;
	i = prompt->char_index + next_nl + 1;
	while (nl_offset--)
	{
		tmp = ft_wstrindex(str, i);
		if (*tmp == '\n' || *tmp == '\0')
			break ;
		i++;
	}
	prompt->char_index = i;
	prompt->buffer_index = ft_wstrindex(str, prompt->char_index) - str;
	move_goto(prompt, calc_cursor_pos(prompt, prompt->char_index));
}
