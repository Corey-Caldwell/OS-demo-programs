/*
 * breakstack.c
 *   Use too much stack space.
 */
#include <stdio.h>

void recurse(void)
{
  char c;
  char iptr[10000];

  printf("&c     = 0x%lx, iptr = 0x%lx  ...  ", &c, iptr);
  fflush(stdout);
  c = iptr[0];
  printf("ok\n");
  recurse();  
}

main()
{
  recurse();
}

