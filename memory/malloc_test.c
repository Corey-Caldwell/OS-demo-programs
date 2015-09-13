/*
 * malloc_test.c
 *    Allocate bytes as requested by user.
 *    Print out the address and the value of the break.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main()
{
  void *mem = NULL;
  long size;

  do {
    printf("  mem     = %p\n",mem);
    printf("  sbrk(0) = %p\n",sbrk(0));
    printf("How much memory? ");
    scanf("%ld",&size);

    mem = malloc(size);
  } while (mem != NULL);

  printf("Out of memory.\n");
}
