/*
 * Made by BadproG.com
 *
 * My terminal is xterm-256color.
 * H : 81
 * L : 109
 *
 * source : Briques_de_base_en_C-Interruptions-errno-signaux-setjmp-longjmp--Linux_Mag_N39--mai_2002--9 pages.pdf
 */

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>

int		main()
{
	const char	*name;
	char		*bp;
	char		*term;
	int			height;
	int			width;

	bp = malloc(sizeof(*bp));
	name = "TERM";
	if ((term = getenv(name)) == NULL)
		return (1);
	printf("My terminal is %s.\n", term);
	tgetent(bp, term);
	height = tgetnum ("li");
	width = tgetnum ("co");
	printf("H : %d\nL : %d\n", height, width);
	free(bp);
	return (0);
}
