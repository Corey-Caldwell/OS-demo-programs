/*
  prime.C

  Multithreaded prime number seeker.
  Find a bunch of prime numbers.

  Bryan Clair
  Sep. 2013
*/

#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
using namespace std;

int howmany;  // how many primes are left to find.

//
// isprime: return True if n is prime
//
bool isprime(long n)
{
  long i,s;
  s = (long) sqrt((double) n);

  for (i = 2; i <= s; i++)
    if (n % i == 0) {
      return false; // not prime
    }

  return true;  // it is prime!
}

//
// seek_primes
//    Thread function to look for primes
//
void *seek_primes(void *unused)
{
  long test;
  while (howmany > 0) {
    test = random();
    if (isprime(test)) {
      cout << test << " is prime!" << endl;
      howmany--;
    }
  }
}

//
// usage - print a usage statement and exit
//
void usage(const char *message) {
  cerr << "usage: prime numthreads howmany" << endl;
  if (message) cerr << "       " << message << endl;
  exit(1);
}

//
// main
//    create threads to seek primes, then exit.
//
int main(int argc, char *argv[])
{
  // Check command line arguments
  if (argc != 3) usage(NULL);

  int num_threads = atoi(argv[1]);
  if (num_threads <= 0) usage("numthreads must be > 0");
    
  howmany = atoi(argv[2]);

  // Create threads
  pthread_t thread_id;
  for (int i = 0; i<num_threads; i++) {
    pthread_create(&thread_id,NULL,seek_primes,NULL);
  }

  // Exit main thread without ending program
  pthread_exit(NULL);
}
