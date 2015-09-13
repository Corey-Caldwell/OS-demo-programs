/*
 * family2.C
 *
 *  Create children and wait for them.
 *
 *  Bryan Clair, 2002
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

using namespace std;

//
// cry
//    Print a message eight times at ~1 second intervals
//
void cry(const char *name)
{
  int i;

  while(1) {
    sleep(1);
    cout << name << " is crying!\n";
  }
}

main()
{
  const char *names[] = {"Alice","Bob","Carol"};

  int pid;
  int n;

  // fork off three child processes

  for (n=0; n<3; n++) {
    switch (pid = fork()) {
    case 0:
      // child
      cout << "I'm " << names[n] << ".  My pid is " << getpid();
      cout << ".  My parent's pid is " << getppid() << ".\n";
      cry(names[n]);
      exit(0);

    case -1:
      // fork failed
      perror("fork");
      exit(errno);
      
    default:
      // parent
      break;
    }
  }

  // wait for children to exit.. there are n children at this point

  int status;
  while (n > 0) {
    if ((pid = wait(&status)) > 0) {
      cout << "My child #" << pid << " exited with status " << status << ".\n";
      n--;
    }
  }

  cout << "Parent exiting.\n";
}

