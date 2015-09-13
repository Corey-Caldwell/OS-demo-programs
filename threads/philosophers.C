/*
 * philosophers.C
 *   Dining philosophers
 */

#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include "phillock.h"

using namespace std;

const char *names[] = {"Confucius", "Kant", "Nietzsche", "Plato", "Socrates"};

// One table with five chopsticks for all philosophers
Phil_Lock table;

void *philosopher(void *nptr);

// Controls speed of simulation.. max # of usec to sleep & eat
int waittime;

/*
 * main
 *   Parse args, init, create threads.
 */
int main(int argc, char *argv[])
{
  int speed;

  switch (argc) {
  case 1:
    speed = 1;
    break;
  case 2:
    speed = atoi(argv[1]);
    if ((speed > 0) && (speed <= 10)) break;
    // else fall through
  default:
    cerr << "usage: philosophers [speed]\n";
    cerr << "       speed = 1..9\n";
    exit(1);
  }

  waittime = 10000000/speed;
  srandom(time(NULL));

  pthread_t id;
  int *nptr;

  for (int i = 0; i<5; i++) {
    nptr = new int;
    *nptr = i;
    pthread_create(&id,NULL,philosopher,nptr);
  }

  pthread_exit(0);  // not going to join threads, since they never stop
}

/*
 * philosopher
 */
void *philosopher(void *nptr)
{
  int id = *(int *) nptr;
  const char *name = names[id];

  while(1) {
    // think
    cout << name << " is thinking." << endl;
    usleep(random() % waittime + 1);

    // get sticks
    cout << name << " is hungry." << endl;
    table.Get_Sticks(id);

    // eat
    cout << name << " is eating." << endl;
    usleep(random() % waittime + 1);

    // drop sticks
    table.Drop_Sticks(id);
  }

  delete (int *)nptr;  // never reaches here, but still good form
}
