/*
  noway.C

  Create a race condition which leads to errors.

  Bryan Clair
  2001-15
*/

#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

int a;

void *one(void *v)
{
  int i;
  while (1) {
    for (i = 0; i < 1000; i++);
    a = 1;
    if (a != 1) {
      cout << "No way! It's not one?\n";
    }
  }
}

void *two(void *v)
{
  int i;
  while (1) {
    for (i = 0; i < 1000; i++);
    a = 2;
    if (a != 2) {
      cout << "No way! It's not two?\n";
    }
  }
}

main()
{
  pthread_t tone, ttwo;

  /* make new threads */
  pthread_create(&tone,NULL,one,NULL);
  pthread_create(&ttwo,NULL,two,NULL);

  /* report on activity */
  while (1) {
    cout << "a = " << a << endl;
    sleep(1);
  }
}  
