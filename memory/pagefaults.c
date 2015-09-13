/*
 * pagefaults.c
 *
 * usage: pagefaults <chunks>
 *
 * Allocate a ton of memory, then write to it.
 * Specifically, allocate <chunks> blocks of memory,
 * each of which consists of PGS_PER_CHUNK pages.
 *
 * When <chunks> is large enough, this program will
 * generate huge numbers of page faults and slow down
 * dramatically.
 *
 * Bryan Clair, 2004-2013
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PGS_PER_CHUNK 16384

main(int argc, char *argv[])
{
  int chunks;

  /* data is an array of pointers to chunks */
  char **data;

  if (argc != 2) {
    fprintf(stderr,"usage: pagefaults <chunks>\n");
    exit(0);
  }

  chunks = atoi(argv[1]);

  /* Allocate (insignificant) space for pointers */
  data = (char **) malloc(chunks * sizeof(char *));

  int pagesize = sysconf(_SC_PAGESIZE);
  unsigned long totalbytes = (long)pagesize * PGS_PER_CHUNK * chunks;
  printf("Going to use %ld bytes, or %ldM.\n",totalbytes,totalbytes >> 20);

  /* Allocate memory and write into every page */
  int i,j;
  for (i = 0; i < chunks; i++) {
    printf("allocating chunk %d\n",i);
    data[i] = (char *) malloc(pagesize * PGS_PER_CHUNK);
    if (data[i] == NULL) {
      printf("Out of memory.\n");
      exit(0);
    }
    for (j = 0; j < PGS_PER_CHUNK; j++) {
      *(data[i]+j*pagesize) = 'B';
      *(data[i]+j*pagesize + 1) = 'C';
    }
  }

  /* Run back through and write to every page again */
  for (i = 0; i < chunks; i++) {
    printf("touching %d\n",i);
    for (j = 0; j < PGS_PER_CHUNK; j++) {
      *(data[i]+j*pagesize) = 'O';
      *(data[i]+j*pagesize + 1) = 'S';
    }
  }
}


