/*
 * yell.c
 *  Create four threads which yell various strings.
 *  Bryan Clair 2006-2015
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *yell(void *word)
{
  int i;

  for (i=0; i<5; i++) {
    sleep(1);
    printf("%s\n",(char *) word);
  }
}

main()
{
  pthread_t thread_id[4];
  char *words[] = {"Sure did.","No way!","Uh huh!","Dang!"};
  int i;
  
  for (i=0; i<4; i++) {
    if (pthread_create(&thread_id[i], NULL, yell, words[i])) {
      perror("Creating thread");
      exit(1);
    }
  }

  for (i=0; i<4; i++) {
    pthread_join(thread_id[i],NULL);
  }
}
