/*
 * child.C
 *
 *  Create a child process.
 *
 *  Bryan Clair, 2002
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
using namespace std;

main() {
  int pid;

  switch (pid = fork()) {
  case 0:
    // child
    cout << "I'm the child.  My pid is " << getpid() << ". ";
    cout << "My parent's pid is " << getppid() << ".\n";
    break;

  case -1:
    // fork failed
    perror("fork");
    exit(errno);

  default:
    // parent
    cout << "I'm the parent.  My pid is " << getpid() << ". ";
    cout << "My child's pid is " << pid << ".\n";
    break;
  }

  cout << "Process #" << getpid() << " exiting.\n";
}

