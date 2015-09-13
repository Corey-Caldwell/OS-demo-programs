/*
 * order_in.C
 *  Create two threads which use semaphores to ensure
 *  they run in predetermined order.
 */
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
using namespace std;

sem_t synch;

void *blurt1(void *unused)
{
  usleep(random() % 1000000);
  sem_wait(&synch);
  cout << "1 2 3 not it!" << endl;
}

void *blurt2(void *unused)
{
  usleep(random() % 1000000);
  cout << "shotgun!" << endl;
  sem_post(&synch);
}

main()
{
  srandom(time(NULL));

  sem_init(&synch,0,0);

  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, blurt1, NULL);
  pthread_create(&thread2, NULL, blurt2, NULL);
  
  pthread_join(thread1,NULL);
  pthread_join(thread2,NULL);
}
