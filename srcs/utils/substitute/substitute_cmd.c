/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 14:23:53 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/30 23:10:35 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

static size_t	delimit_cmdsubst(t_subst *subst)
{
	size_t	j;
	size_t	stack_size;

	j = subst->i + 2;
	stack_size = subst->stack.size;
	subst->err = stack_push(&subst->stack, T_CMDSUBST);
	while (subst->str[j] && subst->err == SH_SUCCESS &&
		stack_size != subst->stack.size)
	{
		if (!is_escaped(&subst->stack, subst->str, j))
			subst->err = delim_handle_specials(&subst->stack, subst->str, j);
		j++;
	}
	if (!subst->str[j] && stack_size != subst->stack.size)
	{
		ft_dprintf(2, "42sh: parse error\n");
		subst->err = SH_ERR_SYNTAX;
	}
	return (j - subst->i);
}

static void		setup_fds(t_subst *subst, int *pipe_, int *new_fd)
{
	if (pipe(pipe_) != 0)
	{
		subst->err = SH_ERR_PIPE;
		return ;
	}
	if ((*new_fd = dup(SH_OUT)) == -1)
	{
		close(pipe_[0]);
		close(pipe_[1]);
		subst->err = SH_ERR_DUP;
		return ;
	}
	close(SH_OUT);
	if (dup2(pipe_[1], SH_OUT) == -1)
	{
		close(pipe_[0]);
		close(pipe_[1]);
		close(*new_fd);
		subst->err = SH_ERR_DUP;
		return ;
	}
	close(pipe_[1]);
}

static void		read_pipe(t_subst *subst, int pipe_in)
{
	char	buffer[256];
	ssize_t	j;

	while (subst->err == SH_SUCCESS &&
		(j = read(pipe_in, buffer, 255)) > 0)
	{
		buffer[j] = '\0';
		subst->err = buff_append(&subst->buffer, buffer);
	}
	while (subst->buffer.size &&
		subst->buffer.buffer[subst->buffer.size - 1] == '\n')
		buff_remove(&subst->buffer, subst->buffer.size - 1);
	close(pipe_in);
	if (subst->err == SH_SUCCESS && j == -1)
		subst->err = SH_ERR_READ;
}

/*
** NOTE: cmd at this point contains the finishing )
*/

static void		expand_cmdsubst(t_subst *subst, char *cmd)
{
	t_lexer	lexer_;
	int		pipe_[2];
	int		new_fd;
	int		ret;

	cmd[ft_strlen(cmd) - 1] = '\n';
	setup_fds(subst, pipe_, &new_fd);
	ft_bzero(&lexer_, sizeof(lexer_));
	if (subst->err != SH_SUCCESS)
		return ;
	lexer_.block_sigtstp = 1;
	if ((ret = lexer(cmd, &lexer_, subst->shell)) == SH_SUCCESS)
	{
		exec_tree(subst->shell, lexer_.build.head);
	}
	else
		free_tree(lexer_.build.head);
	close(SH_OUT);
	lexer_free(&lexer_);
	read_pipe(subst, pipe_[0]);
	dup2(new_fd, SH_OUT);
	close(new_fd);
}

void			substitute_cmd(t_subst *subst)
{
	char	*tmp;
	size_t	j;

	j = delimit_cmdsubst(subst);
	if (subst->err != SH_SUCCESS)
		return ;
	if (!(tmp = ft_strndup(subst->str + subst->i, j)))
	{
		subst->err = SH_ERR_MALLOC;
		return ;
	}
	expand_cmdsubst(subst, tmp + 2);
	free(tmp);
	subst->i += j;
}
