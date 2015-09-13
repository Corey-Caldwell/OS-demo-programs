/*
 * mapfile.C
 *
 * usage: mapfile filename offset
 *   Map the file <filename> into memory beginning at page <offset>.  Dump it to the screen.
 *   Read a line of input, and store it at the beginning of the mapping.
 *
 * Bryan Clair 2010
 */

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

using namespace std;

// usage
//   Print a usage statement, with optional extra message, then exit
//
void usage(const char *msg) {
    cerr << "usage: mapfile filename offset" << endl;
    if (msg) cerr << "       " << msg << endl;
    exit(1);
}

// main
//
int main(int argc, char *argv[]) {
  if (argc != 3) usage(NULL);

  // Get # of pages to offset from command line, calculate byte offset
  int pagesize = sysconf(_SC_PAGESIZE);
  int pageoffset = atoi(argv[2]);
  if (pageoffset < 0) usage("offset must be non-negative");
  size_t offset = pageoffset * pagesize;
  
  // Open the file
  int fd = open(argv[1], O_RDWR);
  if (fd == -1) {
    perror(argv[1]);
    exit(errno);
  }

  // Map the file into memory: 1 page of the file, starting at byte 'offset'.
  char *thefile =
    (char *) mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
  if (thefile == MAP_FAILED) {
    perror(argv[1]);
    exit(errno);
  }

  // Dump the mapped portion of the file
  int byte=0;
  while (byte < pagesize) {
    if (isprint(thefile[byte])) cout << thefile[byte];
    else cout << '.';
    byte++;
    if (byte % 64 == 0) cout << endl;
  }

  // Allow the user to type into the first part of the file mapping:
  cin.getline(thefile, pagesize);

  // Close the mapped file
  munmap(thefile, pagesize);
}
