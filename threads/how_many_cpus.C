/*
 * how_many_cpus.C
 *
 *   Prints the number of cpus (cores) on this machine.
 *   Hopefully, platform indpendent.  Tested for Mac OS X, Ubuntu Linux.
 *
 *   Bryan Clair
 *   2010
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysctl.h>

int main() {
  int cpus = -1;
  
#if defined(__linux__)
  cpus = sysconf( _SC_NPROCESSORS_ONLN );
#elif defined(__APPLE__) || defined(MACOSX)
  size_t size=sizeof(cpus);
  sysctlbyname("hw.ncpu",&cpus,&size,NULL,0);
#else
#error "No CPU-counting code for this OS"
#endif

  if (cpus < 0) {
    perror("Getting # of CPUs");
    exit(1);
  }
  
  printf("This machine has %d cpus.\n",cpus);
}
