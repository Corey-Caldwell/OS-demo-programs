/*
 * Test program for Tanenbaum Chapter 1 Exercise 20
 *   The 'lseek problem'
 *
 * usage: lseek-question filename
 *
 * Bryan Clair 2010
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

  unsigned char buffer[4];
  lseek(fd, 3, SEEK_SET);
  int count = read(fd,buffer,4);
  if (count < 0) {
    perror("read");
    exit(errno);
  }

  for (int i=0; i<count; i++) {
    if (isprint(buffer[i])) cout << buffer[i];
    else cout << ':' << (int) buffer[i] << ':';
  }
  cout << endl;

  if (close(fd)) {
    perror(argv[1]);
    exit(errno);
  }
}
