/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_make_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:44:44 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/16 00:59:48 by wbraeckm         ###   ########.fr       */
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

static void		build_array_proc(t_proc *proc, char **array, size_t *i)
{
	size_t	count;
	t_redir	*redir;

	count = 0;
	while (count < proc->assignments.size)
		array[(*i)++] = (char*)ft_vecget(&proc->assignments, count++);
	count = 0;
	while (count < proc->unprocessed_argv.size)
		array[(*i)++] = (char*)ft_vecget(&proc->unprocessed_argv, count++);
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

int				proc_make_string(t_proc *proc)
{
	char	**array;
	size_t	len;
	size_t	i;

	len = count_nb_words_proc(proc);
	if (proc->next)
		len++;
	if (!(array = ft_memalloc(sizeof(char*) * (len + 1))))
		return (SH_ERR_MALLOC);
	i = 0;
	build_array_proc(proc, array, &i);
	if (proc->next)
		array[i] = "|";
	if (!(proc->proc_str = ft_tabjoin(array, " ")))
	{
		free(array);
		return (SH_ERR_MALLOC);
	}
	free(array);
	return (SH_SUCCESS);
}
