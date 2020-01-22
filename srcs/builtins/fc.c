/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <wdaher-a@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:11:46 by wdaher-a          #+#    #+#             */
/*   Updated: 2020/01/22 17:53:08 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** NOTE: The fc utility shall list, or shall edit and re-execute,
** commands previously entered to an interactive sh.
*/

/*
** TODO:
** free fc after use
**
*/

extern int	g_optopt;

static int	set_options(int ac, char **av, t_fc *as)
{
	char	c;
	int		ret;

	ft_bzero(as->opt, 5);
	ret =  SH_SUCCESS;
	while ((c = ft_getopt(ac, av, "elnrs")) != -1 && ret ==  SH_SUCCESS)
	{
		if (c == 'n')
			as->n = 1;
		if (c == 'r')
			as->rev = 1;
		if (c == 'e' && !ft_strchr(as->opt, 'e') &&
		(!ft_strchr(as->opt, 'l') && !ft_strchr(as->opt, 's')))
			ft_strcat(as->opt, "e");
		else if (c == 'l' && !ft_strchr(as->opt, 'l') &&
		(!ft_strchr(as->opt, 's') && !ft_strchr(as->opt, 'e')))
			ft_strcat(as->opt, "l");
		else if (c == 's' && !ft_strchr(as->opt, 's') &&
		(!ft_strchr(as->opt, 'e') && !ft_strchr(as->opt, 'l')))
			ft_strcat(as->opt, "s");
		else
		{
			ret = NO_ARG;
			ft_dprintf(2, "fc: bad options: %c\n", g_optopt);
		}

	}
	return (ret);
}

static int	fc_parser(int ac, char **av, t_fc *as)
{
	int		i;
	int		ret;

	i = 1;
	ret = SH_SUCCESS;
	while (i < ac && ret == SH_SUCCESS)
	{
		if (!ft_strchr(av[i], '-') && ft_strchr(av[i], '='))
		{
			if (!(as->old_new = ft_strsplit(av[i], '=')))
				ret = SH_ERR_MALLOC;
		}
		if (!ft_strchr(av[i], '-') && !ft_strchr(av[i], '='))
		{
			if (!as->f)
				as->f = av[i];
			if (!as->l && av[i + 1])
				if (!ft_strchr(av[i + 1], '-') && !ft_strchr(av[i + 1], '='))
					as->l = av[i + 1];
		}
		++i;
	}
	ret = set_options(ac, av, as);
	return (ret);
}

static int	simple_list(t_sh *shell, t_fc *args, int rev, int nonumber)
{
	int		i;

	if (shell->history.size <= 0)
		return (SH_ERR_NOEXIST);
	i = (rev) ? args->end - 1 : args->start;
	while (i >= args->start && i < args->end)
	{
		if (nonumber)
			ft_printf("%s\n", shell->history.vec[i]);
		else
			ft_printf("%d  %s\n", i, shell->history.vec[i]);
		i = (rev) ? --i : ++i;
	}
	return (SH_SUCCESS);
}

static int	fc_l_option(t_sh *shell, t_fc *args)
{
	int		i;

	i = shell->history.size - 1;
	while (i >= 0 && shell->history.vec[i])
	{
		if (args->f && ft_strstartswith(shell->history.vec[i], args->f))
		{
			args->start = i;
			while (i < (int)shell->history.size)
			{
				if (args->l && ft_strstartswith(shell->history.vec[i], args->l))
				{
					args->end = i;
					break ;
				}
				++i;
			}
			break ;
		}
		--i;
	}
	simple_list(shell, args, args->rev, args->n);
	return (SH_SUCCESS);
}

static int	get_last_command(t_sh *shell, t_fc *as, char **command)
{
	int		i;
	int		ret;

	if (!shell || !as)
		return (SH_ERR);
	ret = SH_SUCCESS;
	i = (as->rev) ? 0 : shell->history.size - 1;
	while (i >= 0 && i < (int)shell->history.size && as->f)
	{
		if (ft_strstartswith(shell->history.vec[i], as->f))
			break ;
		if (as->rev)
			++i;
		else
			--i;
	}
	if (i >= 0 && i < (int)shell->history.size)
	{
		*command = ft_strdup(shell->history.vec[i]);
		if (!command)
			return (SH_ERR_MALLOC);
		ret = remove_history(shell, i);
	}
	//if (as->old_new && ft_strstartswith(*command, as->old_new[0]))
		//ft_strsreplall(*command, as->old_new[0], as->old_new[1]);
	return (ret);
}

int		fc_e_option(t_sh *shell, t_fc *as, char **command)
{
	int		ret;

	ret = get_last_command(shell, as, command);
	if (command ==  NULL)
		return (ret);
	if ((as->fd = open("/tmp/.42sh_tmp_fc", O_RDWR | O_CREAT | O_TRUNC, 0755)) == -1)
		return (SH_ERR_OPEN);
	ft_dprintf(as->fd, *command);
	close(as->fd);
	ret = run_command(shell, ft_strjoin(as->ed, " /tmp/.42sh_tmp_fc"));
	// here i need to get back that edited line;
	ret = unlink("/tmp/.42sh_tmp_fc");
	return (ret);
}

int		fc_s_option(t_sh *shell, t_fc *as, char **command)
{
	int		ret;
	char	*tmp;

	ret =  SH_SUCCESS;
	tmp =  NULL;
	as->rev = 0;
	ret = get_last_command(shell, as, &tmp);
	if (tmp)
		*command = tmp;
	//here i need to execute retrieved command
	return (ret);
}

int		fc_builtin(int argc, char **argv, t_sh *shell)
{
	t_fc	*as;
	int		ret;
	char	*command;

	if (argc == 1)
		return (SH_SUCCESS);
	as = init_fc(shell);
	ret = SH_SUCCESS;
	if (fc_parser(argc, argv, as) > 0)
		ret = SH_ERR_NOEXIST;
	if (ft_strchr(as->opt, 'l'))
		ret = fc_l_option(shell, as);
	if (ft_strchr(as->opt, 'e') || ft_strlen(as->opt) < 1)
		ret = fc_e_option(shell, as, &command);
	if (ft_strchr(as->opt, 's'))
		ret = fc_s_option(shell, as, &command);
	//ret = free_fc(as);
	return (ret);
}
