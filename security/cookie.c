/*
 *  cookie.c
 *
 *  Make the cookie bad to win.
 */
#include <stdio.h>
#include <string.h>

int main() {
  char buf[16];
  char cookie[5];
  strcpy(cookie,"good");

  printf("Address of buf: %p, of cookie: %p\n", buf, cookie);
  printf("\nWhat kind of cookies do you want? ");
  gets(buf);
  
  printf("cookie is %s\n",cookie);
  if (!strcmp(cookie,"bad"))
    printf("you win!\n");
}
