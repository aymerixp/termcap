/* Menu - long jump if a ^C seen  */
#include <signal.h>
#include <setjmp.h>
#include <stdio.h>

sigjmp_buf jmpbuf;
volatile int canjump = 0;        /* Tells if jump point available */
extern void sig_int(int signo);  /* Signal handler */
void fatal(void) {exit(21); }    /* For various signal errors */

int main() { return menu_wrapper(); }

int menu_wrapper(void) { /* Set up signal handler then call menu() */
   sigset_t sset;
   struct sigaction act, oldact;

   sigemptyset(&sset);
   act.sa_handler = sig_int;
   act.sa_mask = sset;
   act.sa_flags = SA_RESTART;  /* Restart sys calls if siglongjump bypassed */
   if (-1 == sigaction(SIGINT,&act,&oldact)) fatal(); /* Install sig action */
 menu();
   if (-1 == sigaction(SIGINT,&oldact,NULL)) fatal(); /* Restore old action */
   printf("Finished menu\n");
   return 0;
}

int menu(void) {
   volatile int c;  /* volatile: after long jump c not restored */ 
   int flag_interrupt = 0;
   char buf[1024];   
   
   /* sigsetjmp returns with 0 the first time.  Other returns occur
      through siglongjmp, and the return value is the nonzero 2nd arg */
   if (sigsetjmp(jmpbuf, 1 /* Non zero means also save signal mask */ )) {
      fprintf(stderr,"Longjmped after catching a ^C\n");  
      fprintf(stderr,"Pretending to patch data structures.\n");
      flag_interrupt = 1;  /* Could use this flag below */
   }
   canjump = 1;
   
   printf("ENTER: i = infinite loop, t = throw away ^C, q = quit\n");
   while ((c = getchar()) != EOF) switch (c) {
      case 'i':  for (;;); /* infinite loop */ break;
      case 't':  /* This shows that system calls are restarted */
	 canjump = 0;      /* Make handler ignore jump point */
	 while ((c = getchar()) != EOF && c != '\n'); /* Clear line */
	 printf("Throwing away any ^C you type while line entered. ");
	 printf("The read will be restarted.\n");
	 fgets(buf,1023,stdin);
	 printf("\nStuff read since last ^C: %s\n",buf);
	 printf("Handling ^C via longjump again.\n");
	 canjump = 1;
      default :   printf("Enter: i = infinite loop, t = throw away ^C, q = quit\n");
      case '\n':  break;
      case 'q':   return 0;
   }
}

void sig_int(int signo) {     /****  Signal handler ****/
   if (canjump == 0) return;  /* Jump point not ready - unexpected signal */
   canjump = 0;
   siglongjmp(jmpbuf,
	      1 /* The nonzero value sigsetjump returns: 0 is coerced to 1 */);
}
