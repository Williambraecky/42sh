/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_make_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:06:46 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/16 00:59:00 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** NOTE: redirections * 2 because the filename is also contained
*/

static size_t	count_nb_words_proc(t_proc *proc)
{
	size_t	len;
	size_t	i;
	t_redir	*redir;

	len = proc->unprocessed_argv.size + proc->assignments.size;
	i = 0;
	while (i < proc->redirections.size)
	{
		redir = ft_vecget(&proc->redirections, i);
		if (redir->io_nb)
			len++;
		len += 2;
		i++;
	}
	return (len);
}

static size_t	count_nb_words(t_cmd *cmd)
{
	size_t	len;
	t_proc	*curr;

	len = 0;
	curr = cmd->pipeline;
	while (curr)
	{
		len += count_nb_words_proc(curr);
		if (curr->next)
			len++;
		curr = curr->next;
	}
	return (len);
}

static void		build_array_proc(t_proc *proc, char **array, size_t *i)
{
	size_t	count;
	t_redir	*redir;

	count = 0;
	while (count < proc->assignments.size)
		array[(*i)++] = (char*)ft_vecget(&proc->assignments, count++);
	count = 0;
	while (count < proc->unprocessed_argv.size)
	{
		array[(*i)++] =
			(char*)ft_vecget(&proc->unprocessed_argv, count++);
	}
	count = 0;
	while (count < proc->redirections.size)
	{
		redir = (t_redir*)ft_vecget(&proc->redirections, count++);
		if (redir->io_nb)
			array[(*i)++] = redir->io_nb->token.str;
		array[(*i)++] = redir->token->str;
		array[(*i)++] = redir->filename;
	}
}

static void		build_array(t_cmd *cmd, char **array, size_t *i)
{
	t_proc *curr;

	curr = cmd->pipeline;
	while (curr)
	{
		build_array_proc(curr, array, i);
		if (curr->next)
			array[(*i)++] = "|";
		curr = curr->next;
	}
}

/*
** NOTE: makes a cmd string from whole t_cmd and applies it to t_cmd
*/

int				cmd_make_string(t_cmd *cmd)
{
	char	**array;
	size_t	len;
	size_t	i;

	len = count_nb_words(cmd);
	if (cmd->background == 1)
		len++;
	if (!(array = ft_memalloc(sizeof(char*) * (len + 1))))
		return (SH_ERR_MALLOC);
	i = 0;
	build_array(cmd, array, &i);
	if (cmd->background == 1)
		array[i] = "&";
	if (!(cmd->cmd_str = ft_tabjoin(array, " ")))
	{
		free(array);
		return (SH_ERR_MALLOC);
	}
	free(array);
	return (SH_SUCCESS);
}
