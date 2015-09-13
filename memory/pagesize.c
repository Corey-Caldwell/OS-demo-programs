/*
 * pagesize.c
 *   Report size of memory management pages.
 */

#include <stdio.h>
#include <unistd.h>

main()
{
  //  printf("%ld\n",getpagesize());   // not POSIX
  printf("%ld\n",sysconf(_SC_PAGESIZE));
}
