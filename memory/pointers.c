/*
 * pointers.c
 *   Display logical memory addresses of interesting parts of the process'
 *   virtual memory space.
 * 
 * Bryan Clair
 * 2002-2006
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * Linker constants
 *   Try compiling with "gcc -Xlinker -M ...." to see some of these (or not)
 */
extern _end;
extern data_start;
extern _edata;
extern _etext;
extern _start;

void memdump(char *start, char *end);

/*
 * global variables, one initialized, one not.
 */
int global_uninit;
char global_init = '$';

/*
 * proc
 *    A procedure with a local variable
 */
void proc(void)
{
  int i;
  printf("&i               = %p\n", &i);
}

main()
{
  int local;
  void *somememory;

  printf("Break:\n");
  printf(" sbrk(0)= %p\n", sbrk(0));
  printf("\n");

  printf("Text region:\n");
  printf("&_start = %p\n", &_start);
  printf("&_etext = %p\n", &_etext);
  printf("\n");

  printf("Data region:\n");
  printf("&data_start = %p\n", &data_start);
  printf("&_edata = %p\n", &_edata);
  printf("&_end   = %p\n", &_end);
  printf("\n");

  printf("Procedures and variables:\n");
  printf("main()           = %p\n", main);
  printf("memdump()        = %p\n", memdump);
  printf("perror()         = %p\n", perror);
  printf("malloc()         = %p\n", malloc);
  printf("&errno           = %p\n", &errno);
  printf("&local           = %p\n", &local);
  printf("&global_uninit   = %p\n", &global_uninit);
  printf("&global_init     = %p\n", &global_init);

  somememory = malloc(1024);
  printf("somememory       = %p\n", somememory);

  proc();
  
  printf("\n");
  /* dump memory in initialized data region */
  memdump((char *) &data_start,(char *) &_edata);

  printf("Break:\n");
  printf(" sbrk(0)= %p\n", sbrk(0));
  printf("\n");

  printf("Hit ctrl-C to kill.\n");
  while (1) sleep(10);
}

void memdump(char *start, char *end)
{
  char *i;
  int j = 0;

  printf("Memory contents from %p to %p:\n",start,end);

  for (i = start; i < end; i++) {
    // print *i if it's a printable character, else print a dot
    putchar(isprint(*i) ? *i : '.');

    // linebreak every 64 chars
    if (!((++j)%64)) putchar('\n');
  }

  putchar('\n');
}

