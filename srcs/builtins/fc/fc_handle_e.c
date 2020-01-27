/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_handle_e.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 02:51:56 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/27 23:04:03 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	write_history_to_file(t_sh *shell, t_fc *fc, char *filename)
{
	int		fd;
	size_t	*range;
	size_t	i;
	size_t	max;

	max = fc->first >= fc->last ?
		fc->first - fc->last + 1 : fc->last - fc->first + 1;
	range = fc_make_range(fc->first, fc->last);
	i = fc->opt_r ? max : 0;
	if ((fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
		return (1);
	while (range && (fc->opt_r ? i-- : i < max))
	{
		ft_dprintf(fd, "%s\n", ft_vecget(&shell->history, range[i]));
		if (!fc->opt_r)
			i++;
	}
	free(range);
	close(fd);
	return (0);
}

static int	fc_do_edit(t_sh *shell, t_fc *fc, char *filename)
{
	char	*command;

	if (fc->editor == NULL &&
		get_var(shell, "FCEDIT", &fc->editor) != SH_SUCCESS)
		fc->editor = "vim";
	shell->block_history = 1;
	if ((command = ft_strformat("%s %s\n", fc->editor, filename)))
		run_command(shell, command);
	else
	{
		shell->block_history = 0;
		ft_dprintf(2, "42sh: fc: malloc error\n");
		return (1);
	}
	free(command);
	shell->block_history = 0;
	return (get_exit_code(shell));
}

static int	fc_exec_edited(t_sh *shell, char *filename)
{
	int		fd;
	char	*command;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_dprintf(2, "42sh: fc: error opening %s\n", filename);
		return (1);
	}
	if (!(command = file_to_str(fd)) || fc_ensure_newline(&command))
	{
		close(fd);
		unlink(filename);
		free(filename);
		ft_dprintf(2, "42sh: fc: malloc error\n");
		return (1);
	}
	ft_printf("%s", command);
	run_command(shell, command);
	free(command);
	close(fd);
	unlink(filename);
	free(filename);
	return (get_exit_code(shell) > 0);
}

int			fc_handle_edit(t_sh *shell, t_fc *fc)
{
	char	*filename;

	if (!(filename = fc_get_filename()))
	{
		ft_dprintf(2, "42sh: fc: malloc error\n");
		return (1);
	}
	if (write_history_to_file(shell, fc, filename))
	{
		ft_dprintf(2, "42sh: fc: error writing to %s\n", filename);
		free(filename);
		return (1);
	}
	if (fc_do_edit(shell, fc, filename))
	{
		unlink(filename);
		free(filename);
		return (1);
	}
	return (fc_exec_edited(shell, filename));
}
