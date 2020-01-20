/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:26:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/21 00:51:33 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"

/*
** NOTE: prints current jobs from memory with
**   current status and filtering option
** https://pubs.opengroup.org/onlinepubs/9699919799/utilities/jobs.html
** TODO: use argv for job_id
*/

static void	print_cmd(t_cmd *cmd, size_t index, size_t max, int lpflag)
{
	t_proc	*curr;
	size_t	len;

	(void)lpflag;
	len = ft_intlen(index);
	curr = cmd->pipeline;
	while (curr)
	{
		if (curr == cmd->pipeline)
		{
			ft_printf("[%zu] ", index);
			if (index == max)
				ft_printf(" + ");
			else if (index == max - 1)
				ft_printf(" - ");
			else
				ft_printf("   ");
		}
		else
			ft_printf("%*s    ", len + 2);
		ft_printf("%d %-*s(%d) %s\n", curr->pid, 10, "temp", curr->status,
			curr->proc_str);
		curr = curr->next;
	}
}

/*
** TODO: get_signal_str here is wrong
*/

static void	basic_print(t_cmd *cmd, size_t index, size_t max)
{
	t_proc	*curr;
	size_t	len;

	len = ft_intlen(index);
	curr = cmd->pipeline;
	ft_printf("[%zu] ", index);
	if (index == max)
		ft_printf(" + ");
	else if (index == max - 1)
		ft_printf(" - ");
	else
		ft_printf("   ");
	ft_printf("%-*s %s\n", 10, get_signal_str(cmd->pipeline), cmd->cmd_str);
}

static void	print_all(t_sh *shell, int lpflag)
{
	size_t	i;

	i = 0;
	while (i < shell->jobs.size)
	{
		if (lpflag == 0)
			basic_print(ft_vecget(&shell->jobs, i), i + 1, shell->jobs.size);
		else
			print_cmd(ft_vecget(&shell->jobs, i), i + 1,
				shell->jobs.size, lpflag);
		i++;
	}
}

extern int	g_optind;

int			jobs_builtin(int argc, char **argv, t_sh *shell)
{
	int		lpflag;
	int		ret;

	lpflag = 0;
	while ((ret = ft_getopt(argc, argv, "lp")) != -1)
	{
		if (ret == 'l' || ret == 'p')
			lpflag = ret == 'l' ? 2 : 1;
		else
		{
			ft_dprintf(2, "42sh: bad option: -%c\n", ret);
			return (1);
		}
	}
	argc -= g_optind;
	argv += g_optind;
	if (argc > 0)
		; //TODO: use argv job_id
	else
		print_all(shell, lpflag);
	return (0);
}
