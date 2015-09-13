/*
 * openclose.C
 *
 * Open and close a file, using perror to report problems
 *
 * usage: openclose filename
 *
 * Bryan Clair 2002
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "usage: " << argv[0] << " filename" << endl;
    exit(1);
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror(argv[1]);
    exit(errno);
  }

  cout << "file " << argv[1] << " opened on file descriptor " << fd << endl;

  if (close(fd)) {
    perror(argv[1]);
    exit(errno);
  }

  cout << "file " << argv[1] << " closed." << endl;
}
