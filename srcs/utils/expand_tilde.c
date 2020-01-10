/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:42:42 by ntom              #+#    #+#             */
/*   Updated: 2020/01/10 16:42:36 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TO DO :
// only unquoted tilde
// at the begining of the WORD
// followed by all the characters before unquoted slash
//			replace by $LOGNAME
// or followed by all characters if no slash
// 			replace by $HOME
//

#include "lexer.h"
#include "sh.h"

static int	replace_logname(t_sh *shell, char **str)
{
	char	tmp[PATH_MAX];
  int   ret;
  char  *tmp1;

  ft_bzero(tmp, PATH_MAX);
	if ((ret = get_env(shell, "HOME", &tmp) > 0))
    return (ret);
  tmp1 = get_last_occur(tmp, '/');
  if (tmp1)
    ft_strcpy(tmp1, (*str + 1));
  return (SH_SUCCESS);
}

static int	replace_home(t_sh *shell, char **str)
{
  char	tmp[PATH_MAX];
  int   ret;

  ft_bzero(tmp, PATH_MAX);
  if ((ret = get_env(shell, "HOME", &tmp) > 0))
    return (ret);
  ft_strcpy(tmp, (*str + 1));
  return (SH_SUCCESS);
}

int			replace_tilde(t_sh *shell, char **str)
{
	if (*str[0] != '~')
		return (SH_SUCCESS);
	else if (*str[1] == '\0' || *str[1] == '/')
		return (replace_home(shell, str));
	else
		return (replace_logname(shell, str));
	return (SH_SUCCESS);
}
