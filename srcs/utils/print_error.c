/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaher-a <wdaher-a@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:04:17 by wdaher-a          #+#    #+#             */
/*   Updated: 2019/12/22 16:06:36 by wdaher-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char        *g_tab_errors[] =
{
    [SH_ERR_NOEXIST] = "Failed to find something",
    [SH_ERR_MALLOC] = "Malloc error",
    [SH_ERR_ENV_NOEXIST] = "Failed to find env",
    [SH_ERR_SYNTAX] = "Syntax error",
    [SH_ERR_OPEN_HIST] = "Failed to open history",
    [SH_ERR_OPEN_DIR] = "Failed to open directory"
};

/*
** void	display_signal(int status, int test_i)
** {
** 	if (status == SIGALRM)
** 		ft_printf("{red}[TIMEOUT]test %d{eoc}\n", test_i);
** 	else if (status == SIGSEGV)
** 		ft_printf("{red}[SEGV]test %d{eoc}\n", test_i);
** 	else if (status == SIGBUS)
** 		ft_printf("{red}[BUSE]test %d{eoc}\n", test_i);
** 	else if (status == SIGABRT)
** 		ft_printf("{red}[ABRT]test %d{eoc}\n", test_i);
** 	else if (status == SIGFPE)
** 		ft_printf("{red}[FPE]test %d{eoc}\n", test_i);
** 	else
** 		ft_printf("{red}[ERR]test %d ended unexpectedly{eoc}\n", test_i);
** }
**
** void	treat_status(int *success, int test_i)
** {
** 	int		status;
** 	int		result;
**
** 	wait(&status);
** 	if (WIFEXITED(status))
** 	{
** 		result = WEXITSTATUS(status);
** 		if (result == 1)
** 		{
** 			(*success)++;
** 			ft_printf("{green}[OK]test %d{eoc}\n", test_i);
** 		}
** 		else
** 			ft_printf("{red}[KO]test %d{eoc}\n", test_i);
** 	}
** 	else if (WIFSIGNALED(status))
** 		display_signal(status, test_i);
** 	else
** 		ft_printf("{red}[ERR]test %d ended unexpectedly{eoc}\n", test_i);
** }
*/

int     print_error(t_sh *sh, int ret_value)
{
    (void)sh;
    ft_printf("42sh: %s\n", g_tab_errors[ret_value]);
    return (SH_SUCCESS);
}
