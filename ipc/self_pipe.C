/*
 * self_pipe.C
 *
 *   Create a pipe, copy stdin to pipe until eof, then
 *   copy pipe to stdout. 
 *
 * Bryan Clair 2006
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
using namespace std;

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

  cout << "Pipe from " << fdesc[1] << " to " << fdesc[0] << " created.\n";

  // Read from stdin and copy to pipe
  char buf[1024];
  int bytesread;

  while ((bytesread = read(0,buf,1024)) > 0) {
    write(fdesc[1],buf,bytesread);
  }

  // Close the write end of pipe
  close(fdesc[1]);

  // Read from pipe and copy to stdout
  while ((bytesread = read(fdesc[0],buf,1024)) > 0) {
    write(1,buf,bytesread);
  }

  // Close the read end of pipe
  close(fdesc[0]);
}
