/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:26:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/02/07 19:52:27 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"

static void		print_all(t_sh *shell, int lpflag)
{
	size_t	i;

	i = 0;
	while (i < shell->jobs.size)
	{
		if (lpflag == 0)
			basic_print(ft_vecget(&shell->jobs, i), i + 1, shell->jobs.size);
		else if (lpflag == 1)
			print_pflag(ft_vecget(&shell->jobs, i), i + 1, shell->jobs.size);
		else if (lpflag == 2)
			print_lflag(ft_vecget(&shell->jobs, i), i + 1, shell->jobs.size);
		i++;
	}
}

static size_t	job_index(t_sh *shell, t_cmd *cmd)
{
	size_t	i;

	i = shell->jobs.size;
	while (i--)
		if (ft_vecget(&shell->jobs, i) == cmd)
			return (i);
	return (i);
}

static int		print_args(t_sh *shell, int argc, char **argv, int lpflag)
{
	t_cmd	*job;
	size_t	index;
	int		i;

	i = 0;
	while (i < argc)
	{
		job = job_by_id(shell, argv[argc]);
		if (!job)
		{
			ft_dprintf(2, "42sh: jobs: %s: no such job\n", argv[i]);
			return (127);
		}
		index = job_index(shell, job);
		if (lpflag == 0)
			basic_print(job, index + 1, shell->jobs.size);
		else if (lpflag == 1)
			print_pflag(job, index + 1, shell->jobs.size);
		else if (lpflag == 2)
			basic_print(job, index + 1, shell->jobs.size);
	}
	return (0);
}

extern int	g_optind;
extern int	g_optopt;

int				jobs_builtin(int argc, char **argv, t_sh *shell)
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
			ft_dprintf(2, "42sh: bad option: -%c\n", g_optopt);
			return (1);
		}
	}
	argc -= g_optind;
	argv += g_optind;
	if (argc > 0)
		return (print_args(shell, argc, argv, lpflag));
	else
		print_all(shell, lpflag);
	return (0);
}
