/*
  prime.C

  Multithreaded prime number seeker.
  Find a bunch of prime numbers.

  usage: prime primesize numthreads
         primesize - bits in each integer

  Bryan Clair
  2013-2015
*/

#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <stdint.h>

using namespace std;

int primesize;  // global holds the # of bits in each integer.

//
// isprime: return True if n is prime
//          Note use of int64_t for a 64-bit integer.
//
bool isprime(int64_t n)
{
  int64_t i,s;
  s = (int64_t) sqrt((double) n) + 1;

  for (i = 2; i <= s; i++)
    if (n % i == 0) {
      return false; // not prime
    }

  return true;  // it is prime!
}

//
// random_bits : return a random n bit integer (64>n>32)
//
int64_t random_bits(int n) {
  return (((int64_t)random()) << n-32) ^ random();
}

//
// seek_primes
//    Thread function to look for primes
//
void *seek_primes(void *unused)
{
  int64_t test;
  while (true) {
    test = random_bits(primesize);
    if (isprime(test)) {
      cout << test << " is prime!" << endl;
    }
  }
}

//
// usage - print a usage statement and exit
//
void usage(const char *message) {
  cerr << "usage: prime primesize numthreads" << endl;
  cerr << "             primesize - bits in each integer" << endl;
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

  primesize = atoi(argv[1]);

  int num_threads = atoi(argv[2]);
  if (num_threads <= 0) usage("numthreads must be > 0");
  

  // Create threads
  pthread_t thread_id;
  for (int i = 0; i<num_threads; i++) {
    pthread_create(&thread_id,NULL,seek_primes,NULL);
  }

  // Exit main thread without ending program
  pthread_exit(NULL);
}
