/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:01:51 by wbraeckm          #+#    #+#             */
/*   Updated: 2020/01/13 19:29:29 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lexer.h"

/*
** TODO:
**  no args:
**   1: for every alias create a string in form key='value'{done}
**   2: sort these string by ascii order{done}
**   3: print them{done}
**   4: ???
**   5: profit
**  with args, for every arg:
**   1: split first arg on = (no need to actually split just replace = with \0)
**   2: validate alias name (should be a-zA-Z0-9 probably)
**   3: tokenize string after = (/!\ lexer should not ask for prompt again)
**   4: add to alias (remove if it exists before)
**   5: ???
**   6: profit
*/

static int	valid_arg(char *string)
{
	char	*tmp;
	int		ret;

	tmp = ft_strchr(string, '=');
	*tmp = '\0';
	ret = 1;
	if (!string || !str_is_name(string))
		ret = 0;
	*tmp = '=';
	return (ret);
}

void	display(t_sh *shell, char **sorted_al)
{
	size_t	i;

	if (!sorted_al)
		return ;
	i = 0;
	while (sorted_al[i])
	{
		ft_printf("%s=%s\n", sorted_al[i], get_alias(shell, sorted_al[i]));
		i++;
	}
}

int	print_aliases(t_sh *shell, t_map *al)
{
	char		**al_tosort;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!(al_tosort=(char**)malloc(sizeof(char*)*al->size)))
		return (SH_ERR_MALLOC);
	i = 0;
	j = 0;
	len = 0;
	while (i < al->size)
	{
		if (al->nodes[i].is_used)
		{
			if (!(al_tosort[j++] = ft_strdup(al->nodes[i].key)))
				return (SH_ERR_DUP);
		}
		++i;
	}
	al_tosort[j] =  NULL;
	ft_strsort(al_tosort, j, &ft_strcmp);
	display(shell, al_tosort);
	return (SH_SUCCESS);
}

int		alias_builtin(int argc, char **argv, t_sh *shell)
{
		char	*tmp;
		size_t	i;
		int		ret;

		if (argc == 1)
			print_aliases(shell, shell->aliases);
		i = 1;
		ret = SH_SUCCESS;
		while (i < (size_t)argc && ret == SH_SUCCESS)
		{
			if ((tmp=ft_strchr(argv[i], '=')) && !valid_arg(argv[i]))
			{
				*tmp = '\0';
				ret = repl_alias(shell, argv[i], (tmp + 1));
				*tmp = '=';
			}
			else
				return (SH_ERR_SYNTAX);
			++i;
		}
		return (ret);
}
