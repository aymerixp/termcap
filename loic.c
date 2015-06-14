/*
 * source : http://loiclefloch.fr/877-les-termcaps/
 *
 * A la compilation, on rajoute l’option : -lncurses
 * gcc -Wall -Werror -Wextra -lncurses loic.c
 *
 */

#include <termios.h>
#include <unistd.h>
#include <term.h>

typedef struct	s_termios {
	tcflag_t c_iflag;
	tcflag_t c_oflag;
	tcflag_t c_cflag;
	tcflag_t c_lflag;
	cc_t c_cc[NCCS];
	speed_t c_ispeed;
	speed_t c_ospeed;
}				t_termios;

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*name_term;
	t_termios term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	// remplis la structure termios des possibilités du terminal.
	if (tcgetattr(0, term) == -1)
		return (-1);

	term.c_lflag &= ~(ICANON); // Met le terminal en mode canonique.
	term.c_lflag &= ~(ECHO); // les touches tapées ne s'inscriront plus dans le terminal
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	// On applique les changements :
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
}
