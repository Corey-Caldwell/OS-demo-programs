/*
 * order_out.C
 *  Create two threads which run in a random order.
 */
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void *blurt1(void *unused)
{
  usleep(random() % 1000000);
  cout << "1 2 3 not it!" << endl;
}

void *blurt2(void *unused)
{
  usleep(random() % 1000000);
  cout << "shotgun!" << endl;
}

main()
{
  srandom(time(NULL));

  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, blurt1, NULL);
  pthread_create(&thread2, NULL, blurt2, NULL);
  
  pthread_join(thread1,NULL);
  pthread_join(thread2,NULL);
}
