/*
 * stderrdemo.c
 *   Demonstrate that stdin is buffered but stderr is not.
 *
 *   Bryan Clair 2008-2015
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
  fprintf(stderr,"tic ");

  printf("ping ");

  fprintf(stderr,"tac ");

  printf("pong ");
  
  sleep(1);

  fprintf(stderr,"toe ");

  printf("\n");
}
