/*
 * pipe_demo.C
 *
 *   Create a pipe for communication, fork a child,
 *   and read messages from that child.
 *
 * Bryan Clair 2003
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
using namespace std;

#define MAX_MSG 256

//
// cry
//
//   print five childish messages at 1 second intervals
//
void cry()
{
  const char *msgs[5] = {"i'm hungry","my turn!","no",
		   "go away", "help me"};

  for (int i=0; i<5; i++) {
    cout << msgs[i] << endl;
    sleep(1);
  }
}


main()
{
  // fdesc is an array of two file descriptors:
  //    fdesc[0] will be the readable end of the pipe
  //    fdesc[1] will be the writable end of the pipe
  int fdesc[2];

  // create the pipe
  if (pipe(fdesc)) {
    perror("pipe failed");
    exit(errno);
  }

  // fork a child
  switch (fork()) {
  case 0:
    // Child
    
    // close the input end of pipe - not needed
    close(fdesc[0]);

    // set the writable end of pipe to be stdout
    dup2(fdesc[1],fileno(stdout));
    close(fdesc[1]);

    // cry to mommy
    cry();
    cerr << "Child exiting." << endl;
    exit(0);

  case -1:
    // fork failed
    perror("fork");
    exit(errno);
      
  default:
    // parent

    // close the output end of pipe
    close(fdesc[1]);

    // set the input end of pipe to be stdin
    dup2(fdesc[0],fileno(stdin));
    close(fdesc[0]);
    break;
  }

  // Parent reads from stdin (hooked to pipe), writes to stdout
  char message[MAX_MSG];
  while (cin.getline(message, MAX_MSG-1)) {
    cout << "My child said '" << message << "'.  How precious.\n";
  }

  wait(NULL);   // wait for child to exit

  cout << "Parent exiting.\n";
  return 0;
}
