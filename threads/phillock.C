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
#include <pthread.h>
#include "phillock.h"

Phil_Lock::Phil_Lock(void)
{
  next_number = 1;
  pthread_mutex_init(&lock,NULL);

  for (int i = 0; i < 5; i++) {
    pthread_cond_init(&ok_to_eat[i],NULL);
    number[i] = 0;
    hungry[i] = false;
    stick_in_use[i] = false;
  }
}

void Phil_Lock::Get_Sticks(int me)
{
  int left_phil = (me + 4) % 5;
  int right_phil = (me + 1) % 5;
  int left_stick = me;
  int right_stick = (me + 1) % 5;

  pthread_mutex_lock(&lock);

  hungry[me] = true;
  number[me] = next_number++;  // take a number

  while (stick_in_use[left_stick] || stick_in_use[right_stick] ||
	 (hungry[left_phil] && (number[left_phil] < number[me])) ||
	 (hungry[right_phil] && (number[right_phil] < number[me])))
    {
      pthread_cond_wait(&ok_to_eat[me],&lock);
    }

  stick_in_use[left_stick] = true;
  stick_in_use[right_stick] = true;
  hungry[me] = false;

  pthread_mutex_unlock(&lock);
}

void Phil_Lock::Drop_Sticks(int me)
{
  int left_phil = (me + 4) % 5;
  int right_phil = (me + 1) % 5;
  int left_stick = me;
  int right_stick = (me + 1) % 5;

  pthread_mutex_lock(&lock);

  stick_in_use[left_stick] = false;
  stick_in_use[right_stick] = false;

  // signal neighbors that it might be ok to eat
  pthread_cond_signal(&ok_to_eat[left_phil]);
  pthread_cond_signal(&ok_to_eat[right_phil]);

  pthread_mutex_unlock(&lock);
}

