/*
  prime.C

  Multithreaded prime number seeker.

  Version 1 divides the range into equal pieces which it distributes
  among the threads.

  Bryan Clair
  Sep. 2008
*/

#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
using namespace std;

long factor(long n);

struct range {
  long start;
  long stop;
};

//
// seek_primes
//    Thread function to look for primes in the range given by the argument.
//    Searches from start value up to (but not including) stop value.
//
void *seek_primes(void *sss)
{
  struct range *r = (struct range *)sss;

  long my_id = pthread_self();
               // generates a unique id for this thread

  for (long n = r->start; n < r->stop; n++) {
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
  if (num_threads <= 0) {
    cerr << "usage: prime numthreads start stop" << endl;
    cerr << "       numthreads must be > 0" << endl;
    exit(1);
  }
    
  long start = atol(argv[2]);
  long stop = atol(argv[3]);
  long width = stop-start+1; // how many numbers need to be tested

  // start and stop values for each thread
  struct range ranges[num_threads];

  // create threads
  pthread_t thread_ids[num_threads];

  for (int i = 0; i<num_threads; i++) {
    ranges[i].start = start + (width * i)/num_threads;
    ranges[i].stop = start + (width * (i+1))/num_threads;

    pthread_create(&thread_ids[i],NULL,seek_primes,&ranges[i]);
  }

  // wait for them to finish
  for (int i = 0; i<num_threads; i++) {
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



