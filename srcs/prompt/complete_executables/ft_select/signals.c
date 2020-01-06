#include "prompt.h"

#include <stdio.h>
/*int		exit_erase(t_sh *shell, t_select *select)
{
	(void)shell;
	(void)select;

	sleep(3);
	tcsetattr(SH_IN, TCSANOW, &(select->old_termios));
	//loop for deleting each lines (up up up cr cd)
//	sleep(3);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
//	sleep(3);
	tputs(tgetstr("up", NULL), 1, ft_putchar);
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	return (SH_SUCCESS);
}*/

/*int		init_signal(void)
{

//	signal(SIGTSTP, //NULL);
//	signal(SIGWINCH, //resize);
	signal(SIGINT, SIG_DFL);
//	signal(SIGTERM, //exit no erase);
	return (0);
}*/
