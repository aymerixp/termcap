/*
 * http://loiclefloch.fr/877-les-termcaps/
 */

/*
#include <termios.h>
#include <unistd.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
*/
#include <stdio.h>
#include <signal.h>
#include <term.h>
#include <termios.h>
#include <termcap.h>
#include <sys/ioctl.h>
#include "../libraire/libft.h"

int		voir_touche();

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*name_term;
	struct termios term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	// remplis la structure termios des possibilités du terminal.
	if (tcgetattr(0, &term) == -1)
		return (-1);
	char	buffer[3];

	while (1)
	{
		read(0, buffer, 3);
		if (buffer[0] == 27)
			printf("C'est une fleche !\n");
		else if (buffer[0] == 4)
		{
			printf("Ctlr+d, on quitte !\n");
			return (0);
		}
	}
	return (0);
}

int		voir_touche()
{
	char	buffer[3];

	while (1)
	{
		read(0, buffer, 3);
		if (buffer[0] == 27)
			printf("C'est une fleche !\n");
		else if (buffer[0] == 4)
		{
			printf("Ctlr+d, on quitte !\n");
			return (0);
		}
	}
	return (0);
}
