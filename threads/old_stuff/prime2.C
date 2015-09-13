/*
  prime2.C

  Multithreaded prime number seeker, version 2.

  Version 2 uses a 'work gang' model, where the threads get their next number
  from a global variable (cur), which then must be protected by a lock.

  This turns out to be slightly faster than V1 because in V1 one thread will
  typically end up having more work than the others, and the program is only
  as fast as it's fastest thread.  Here, all threads finish at essentially
  the same time.

  Bryan Clair
  Sep. 2003
*/

#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
using namespace std;

long factor(long n);

// globals
volatile long cur = 2;
long stop;

pthread_mutex_t curlock;

//
// seek_primes
//    thread function to look for primes
//
void *seek_primes(void *unused)
{
  long n;
  long my_id = pthread_self();
               // generates a unique id for this thread

  while (1) {
    pthread_mutex_lock(&curlock);
    n = cur++;
    pthread_mutex_unlock(&curlock);

    if (n > stop) pthread_exit(0);

    if (factor(n) == 0)
      cout << n << " is prime, says thread #" << my_id << endl;
  }
}


//
// main
//    create threads to seek primes, then exit.
//
int main(int argc, char *argv[])
{
  // parse parameters
  if (argc != 4) {
    cerr << "usage: prime numthreads start stop" << endl;
    exit(1);
  }

  int num_threads = atoi(argv[1]);
  cur = atol(argv[2]);
  stop = atol(argv[3]);

  // create lock on cur (next number to check)
  pthread_mutex_init(&curlock,NULL);

  // create threads
  pthread_t thread_ids[num_threads];

  int i;
  for (i = 0; i<num_threads; i++) {
    pthread_create(&thread_ids[i],NULL,seek_primes,NULL);
  }

  // wait for them to finish
  for (i = 0; i<num_threads; i++) {
    pthread_join(thread_ids[i],NULL);
  }
}

//
// factor - return smallest factor of n, 0 if n is prime.
//
long factor(long n)
{
  long i,s;
  s = (long) sqrt((double) n);

  for (i = 2; i <= s; i++)
    if (n % i == 0) {
      return i; // not prime
    }

  return 0;  // it is prime!
}



