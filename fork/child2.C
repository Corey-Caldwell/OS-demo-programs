/*
 * child2.C
 *
 *  Create a child process.  Parent and child loop.
 *
 *  Bryan Clair, 2008
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
    while (1) {
      cout << "My parent's pid is " << getppid() << ".\n";
      sleep(1);
    }

  case -1:
    // fork failed
    perror("fork");
    exit(errno);

  default:
    // parent
    cout << "I'm the parent.  My pid is " << getpid() << ". ";
    cout << "My child's pid is " << pid << ".\n";
    while (1) {
      cout << "Mommy is here." << endl;
      sleep(1);
    }

  }

}

