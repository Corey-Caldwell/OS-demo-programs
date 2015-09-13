/*
 * phillock.h
 *    Interface to class Phil_Lock
 *
 *    Five philosophers need mutually exclusive access to their chopsticks.
 *    Fair, deadlock free solution with no starvation... "take a number".
 *
 * Bryan Clair
 * 2003
 *
 */
#ifndef PHILLOCK_H
#define PHILLOCK_H

#include <pthread.h>

class Phil_Lock {
public:
  Phil_Lock(void);
  void Get_Sticks(int n);
  void Drop_Sticks(int n);

private:
  pthread_mutex_t lock;
  pthread_cond_t ok_to_eat[5];

  int next_number;
  int number[5];     // philosophers with lower numbers get to eat first
  bool stick_in_use[5];
  bool hungry[5];   // true when philosopher i is waiting for sticks
};

#endif
