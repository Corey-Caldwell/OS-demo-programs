/*
 *  Create a child process and exec over it.
 *  Bryan Clair 2003
 */
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

main() {
  int pid;
  char *psargs[3] = {"ps","j",NULL};

  switch (pid = fork()) {
  case 0:
    // Child
    execvp(psargs[0],psargs);
    // will only reach here if exec fails
    perror(psargs[0]);
    exit(errno);

  case -1:
    // fork failed
    perror("fork");
    exit(errno);

  default:
    // Parent
    wait(NULL);  // wait for my one child, ignore exit status
    printf("Parent exiting.\n");
    exit(0);
  }
}
