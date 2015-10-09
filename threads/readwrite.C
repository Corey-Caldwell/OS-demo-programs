/*
 * readwrite.C
 *   Demo a readers/writers lock
 */

#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "rwlock.h"

using namespace std;

// Global lock for readers & writers
RW_Lock lock;

void *reader(void *v);
void *writer(void *v);

/*
 * main
 *   Parse args, init, create threads.
 */
int main(int argc, char *argv[])
{
  if (argc != 3) {
    cerr << "usage: readwrite numreaders numwriters\n";
    exit(1);
  }

  int nr = atoi(argv[1]);  
  int nw = atoi(argv[2]);

  srandom(time(0));  // seed random number generator
  cout << unitbuf;   // set cout to flush without newlines

  int i;
  pthread_t p;
  int *id;

  for (i = 0; i<nr; i++) {
    id = new int;
    *id = i;
    pthread_create(&p,NULL,reader,id);
  }

  for (i = 0; i<nw; i++) {
    id = new int;
    *id = i;
    pthread_create(&p,NULL,writer,id);
  }

  pthread_exit(0);  // not going to join threads, since they never stop
}

/*
 * reader
 */
void *reader(void *v)
{
  int id = *((int *)v);

  while(1) {
    // pause
    sleep(random()%8);

    // get RW_Lock as a reader
    lock.Reader_Lock();
  
    // "read" for up to 4 seconds
    cout << "(R" << id;
    for (int i=0; i <= random()%4; i++) {
      cout << ".";
      sleep(1);
    }
    cout << ")";

    // release lock
    lock.Reader_Unlock();
  }
}


/*
 * writer
 */
void *writer(void *v)
{
  int id = *((int *)v);

  while(1) {
    // pause
    sleep(random()%8);

    // get RW_Lock as a reader
    lock.Writer_Lock();
  
    // "write" for up to 4 seconds
    cout << "\n(W" << id;
    for (int i=0; i <= random()%4; i++) {
      cout << ".";
      sleep(1);
    }
    cout << ")";

    // release lock
    lock.Writer_Unlock();
  }
}
