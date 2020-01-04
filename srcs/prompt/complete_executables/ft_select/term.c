#include "prompt.h"

int		init_term(t_sh *shell, t_select *select)
{
	(void)shell;
	tcgetattr(SH_IN, &select->old_termios);
	tcgetattr(SH_IN, &(select->current_termios));
	select->current_termios.c_lflag &= ~(ICANON | ECHO); //maybe useless
	select->current_termios.c_cc[VMIN] = 1; //maybe useless
	select->current_termios.c_cc[VTIME] = 0; //maybe useless
	if (tcsetattr(SH_IN, TCSANOW, &(select->current_termios)) == -1)
		return (1);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
//	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	tputs(tgetstr("do", NULL), 1, ft_putchar);
	return (0);
}
