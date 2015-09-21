/*
  way.C

  Eliminating a race condition with mutual exclusion.

  Bryan Clair
  2001-15
*/

#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

int a;

pthread_mutex_t alock;    // Global mutex used to lock access to a


void *one(void *v)
{
  int i;
  while (1) {
    for (i = 0; i < 1000; i++);

    pthread_mutex_lock(&alock);

    /* critical section */
    a = 1;
    if (a != 1) {
      cout << "No way! It's not one?\n";
    }
    /* end critical section */

    pthread_mutex_unlock(&alock);
  }
}

void *two(void *v)
{
  int i;
  while (1) {
    for (i = 0; i < 1000; i++);

    pthread_mutex_lock(&alock);

    /* critical section */
    a = 2;
    if (a != 2) {
      cout << "No way! It's not two?\n";
    }
    /* end critical section */

    pthread_mutex_unlock(&alock);
  }
}

main()
{
  pthread_t tone, ttwo;

  /* initialize mutex */
  pthread_mutex_init(&alock,NULL);

  /* make new threads */
  pthread_create(&tone,NULL,one,NULL);
  pthread_create(&ttwo,NULL,two,NULL);

  /* report on activity */
  while (1) {

    pthread_mutex_lock(&alock);
    cout << "a = " << a << endl;
    pthread_mutex_unlock(&alock);

    sleep(1);
  }
}  
