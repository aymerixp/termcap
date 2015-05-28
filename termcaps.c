/*
 * source : http://openclassrooms.com/forum/sujet/termcaps-probleme-ac-read
 * */
#include <termios.h>
#include <unistd.h>
#include "../libraire/libft.h"
#include <termcap.h>
#include <stdlib.h>
#include <stdio.h>

int		main(int ac, char **av)
{
	struct termios        t;
	t_pos                 *coord;

	tgetent(NULL, "xterm");
	tcgetattr(0, &t);
	t.c_lflag &= ~ICANON;
	t.c_cc[VMIN] = 1;
	t.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &t);
	coord = malloc(sizeof(*coord));
	coord->x = 0;
	coord->y = 0;
	ft_putstr(tgetstr("cl", av));
	while (42)
	{
		where_do_i_go(coord);
		goto_fct(coord->x,coord->y);
		/* my_put_nbr(coord->x); */
		/* my_putchar(10); */
		/* my_put_nbr(coord->y); */
	}
	return (0);
}

void	where_do_i_go(t_pos *coord)
{
	char buffer[2];
	int i;

	i = read(1, &buffer, 3);
	if (i == 0 || i == -1)
		ft_putstr("read failled");
	if (buffer[0] == '^' && buffer[1] == '[')
	{
		if (buffer[2] == 'A')
			coord->y = coord->y + 1;
		else if (buffer[2] == 'B')
			coord->y = coord->y - 1;
		else if (buffer[2] == 'C')
			coord->x = coord->x + 1;
		else if (buffer[2] == 'D')
			coord->x = coord->x - 1;
	}
}
void	window_size()
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	ft_putnbr(w.ws_row);
	ft_putchar(10);
	ft_putnbr(w.ws_col);
}
	 
void goto_fct(int x, int y)
{
	ft_putstr(tgetstr("cl", NULL));
	ft_putstr(tgoto(tgetstr("cm", NULL), x, y));
}
