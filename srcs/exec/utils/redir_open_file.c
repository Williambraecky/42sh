/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_open_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:42:00 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 23:05:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <unistd.h>
#include <fcntl.h>

static int	get_flags_for_type(t_type type)
{
	if (type == T_GREATER || type == T_GREATER_AND)
		return (O_CREAT | O_TRUNC | O_WRONLY);
	else if (type == T_DOUBLE_GREATER)
		return (O_CREAT | O_APPEND | O_WRONLY);
	return (O_CREAT | O_RDONLY);
}

static void	find_error(t_redir *redir, int write)
{
	t_stat	stat_t;

	if (stat(redir->filename, &stat_t) != 0)
		ft_dprintf(2, "42sh: no such file or directory: %s\n", redir->filename);
	else if (S_ISDIR(stat_t.st_mode))
		ft_dprintf(2, "42sh: is a direcotyr: %s\n", redir->filename);
	else if (write && access(redir->filename, W_OK) != 0)
		ft_dprintf(2, "42sh: permission denied: %s\n", redir->filename);
	else if (!write && access(redir->filename, R_OK) != 0)
		ft_dprintf(2, "42sh: permission denied: %s\n", redir->filename);
	else
		ft_dprintf(2, "42sh: error opening file: %s\n", redir->filename);
}

static int	check_redirand_fd(t_redir *redir)
{
	int		fd;

	if (ft_strequ(redir->filename, "-"))
		return (SH_SUCCESS);
	fd = ft_atoi(redir->filename);
	if (fcntl(fd, F_GETFD) == -1)
	{
		ft_dprintf(2, "42sh: %d: bad file descriptor\n", fd);
		return (SH_ERR_OPEN);
	}
	return (SH_SUCCESS);
}

static int	check_redirand(t_redir *redir)
{
	if (redir->token->type != T_LESSER_AND &&
		redir->token->type != T_GREATER_AND)
		return (0);
	if (ft_strequ(redir->filename, "-"))
		return (1);
	if (ft_strisnumber(redir->filename) && ft_atoi(redir->filename) >= 0)
		return (1);
	return (0);
}

int			redir_open_file(t_redir *redir)
{
	int		flag;
	int		fd;

	if (redir->token->type == T_DOUBLE_LESSER)
		return (SH_SUCCESS);
	if (check_redirand(redir))
		return (check_redirand_fd(redir));
	flag = get_flags_for_type(redir->token->type);
	fd = open(redir->filename, flag, 0666);
	if (fd == -1)
	{
		find_error(redir, flag & O_WRONLY);
		return (SH_ERR_OPEN);
	}
	redir->to = fd;
	return (SH_SUCCESS);
}
