/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_git_branch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 23:14:51 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/20 20:30:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

static int	setup_redir(int pipe_[2], int *new_fd)
{
	if (pipe(pipe_) == -1)
		return (SH_ERR_PIPE);
	if ((*new_fd = dup(SH_OUT)) == -1)
	{
		close(pipe_[0]);
		close(pipe_[1]);
		return (SH_ERR_DUP);
	}
	close(SH_OUT);
	if (dup2(pipe_[1], SH_OUT) == -1)
	{
		close(*new_fd);
		close(pipe_[0]);
		close(pipe_[1]);
		return (SH_ERR_DUP);
	}
	close(pipe_[1]);
	return (SH_SUCCESS);
}

static char	*read_output(int fd)
{
	char	buffer[256];
	ssize_t	j;

	j = read(fd, buffer, 255);
	if (j == -1 || j == 0)
		return (ft_strdup(""));
	buffer[j] = '\0';
	if (j > 0 && buffer[j - 1] == '\n')
		buffer[j - 1] = '\0';
	return (ft_strformat("(%s) ", buffer));
}

char		*get_git_branch(t_sh *shell)
{
	t_lexer	lexer_;
	char	*result;
	int		pipe_[2];
	int		new_fd;
	int		ret;

	if (setup_redir(pipe_, &new_fd) != SH_SUCCESS)
		return (ft_strdup(""));
	ft_bzero(&lexer_, sizeof(lexer_));
	shell->block_ret_update = 1;
	if ((ret = lexer("git rev-parse --abbrev-ref HEAD 2>/dev/null",
		&lexer_, shell)) == SH_SUCCESS)
		exec_tree(shell, lexer_.build.head);
	else
		free_tree(lexer_.build.head);
	lexer_free(&lexer_);
	shell->block_ret_update = 0;
	close(SH_OUT);
	dup2(new_fd, SH_OUT);
	close(new_fd);
	result = read_output(pipe_[0]);
	close(pipe_[0]);
	return (result);
}
