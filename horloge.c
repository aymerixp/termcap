#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/*
 *
 * Demarrage (PID #40293Thu May 28 11:58:03 2015
 * Thu May 28 11:58:22 2015
 * Thu May 28 11:58:23 2015 // kill -HUP 40293 :
 * reboot
 * Demarrage (PID #40293Thu May 28 11:58:24 2015
 * Thu May 28 11:58:25 2015
 *
 * source : Briques_de_base_en_C-Interruptions-errno-signaux-setjmp-longjmp--Linux_Mag_N39--mai_2002--9 pages.pdf
 * */

char **my_argv;

void		sighup_handler(int i)
{
	printf("reboot\n");
	execv(my_argv[0], my_argv);
}

int			main(int argc, char **argv)
{
	time_t t;
	printf("Demarrage (PID #%d)\b", getpid());
	my_argv = argv;
	signal(SIGHUP, sighup_handler);
	while (1)
	{
		t = time (0);
		printf("%s", ctime(&t));
		sleep(1);
	}
}
