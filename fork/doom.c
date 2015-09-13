/*
 * doom.c
 *
 *   A "forkbomb"
 *
 *   DO NOT RUN THIS PROGRAM - creates many processes and is
 *                             likely to crash your system
 *
 *  Bryan Clair 2002-2015
 */

#include <unistd.h>

main()
{
  while(1) fork();
}
