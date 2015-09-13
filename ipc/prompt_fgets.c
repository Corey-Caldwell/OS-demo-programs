/*
 * prompt_fgets.C
 *    Repeatedly prompt user for input and echo it back.
 *    Only exits on EOF (^D).  Catches SIGINT (^C) and handles
 *    it correctly while in the middle of an input line.
 *
 * Bryan Clair, 2006
 */

#include <stdio.h>
#include <signal.h>
#include <errno.h>

//
// handle_interrupt
//
void handle_interrupt(int the_sig)
{
}

//
// main
//   Set up signal handling, then enter a loop that prints a prompt,
//   reads a line of text and echoes it back.
//
main()
{
  const int MAX_LINE=256;

  char line[MAX_LINE];

  // Establish signal handler for SIGINT (^C)
  signal(SIGINT,handle_interrupt);
  siginterrupt(SIGINT,1);

  do {
    printf("Type something: ");
    errno = 0;
    if (fgets(line,MAX_LINE,stdin)) {
      printf("You typed: %s",line);
    } else {
      if (errno == EINTR) {
	printf("\n");
      }
    }
  } while (!feof(stdin));

  printf("\n");
}
