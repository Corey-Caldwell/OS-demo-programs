/*
 * probe.c
 *   Let user poke around at arbitrary memory addresses.
 */

#include <stdio.h>

extern data_start;
extern _edata;
extern _etext;
extern _start;

main()
{
  char *s;
  char c;

  printf("Break:\n");
  printf(" sbrk(0)= 0x%lx\n", sbrk(0));
  printf("\n");

  printf("Text region:\n");
  printf("&_start = 0x%lx\n", &_start);
  printf("&_etext = 0x%lx\n", &_etext);
  printf("\n");

  printf("Data region:\n");
  printf("&data_start = 0x%lx\n", &data_start);
  printf("&_edata = 0x%lx\n", &_edata);
  printf("\n");

  printf("Enter memory location in hex: ");
  scanf("%lx", &s);

  printf("Reading 0x%lx:  ", s);
  fflush(stdout);
  c = *s;
  printf("%d\n", c);

  printf("Writing %d back to  0x%lx:  ", c, s);
  fflush(stdout);
  *s = c;
  printf("ok\n");
}



