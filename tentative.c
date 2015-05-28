/*
 * gcc -Wall -Werror -Wextra tentative.c -lcurses
 * */
#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	char buf[1024];
	char buf2[30];
	char *ap;
	ap = buf2;
	char *clearstr;
	char *gotostr;
	char *standstr;
	char *stendstr;

	tgetent(buf, getenv("TERM"));

	clearstr = tgetstr("cl", &ap);
	gotostr = tgetstr("cm", &ap);
	standstr = tgetstr("so", &ap);
	stendstr = tgetstr("se", &ap);

	fputs(clearstr, stdout);
	fputs(tgoto(gotostr, 20, 5), stdout);
	printf("Hello, ");
	fputs(tgoto(gotostr, 20, 10), stdout);
	printf("ABCDE, ");
	fputs(standstr, stdout);
	printf("kdkdkdk world");
	fputs(stendstr, stdout);
	putchar('!');
}

