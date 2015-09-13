/*
 * class RW_Lock provides a readers/writers lock that allows multiple
 * readers or one writer.
 *
 * If writers are waiting to work, no new readers are allowed to get
 * the lock.
 */
#include <pthread.h>
#include "rwlock.h"

RW_Lock::RW_Lock(void)
{
  num_readers = num_writers = 0;
  active_writer = false;
  pthread_mutex_init(&lock,NULL);
  pthread_cond_init(&all_clear,NULL);
  pthread_cond_init(&no_writers,NULL);
}

void RW_Lock::Reader_Lock(void)
{
  pthread_mutex_lock(&lock);
  while (num_writers > 0) {
    pthread_cond_wait(&no_writers,&lock);
  }
  num_readers++;
  pthread_mutex_unlock(&lock);
}

void RW_Lock::Reader_Unlock(void)
{
  pthread_mutex_lock(&lock);
  num_readers--;
  if (num_readers == 0) {
    pthread_cond_signal(&all_clear);     // wake a writer
  }
  pthread_mutex_unlock(&lock);
}


void RW_Lock::Writer_Lock(void)
{
  pthread_mutex_lock(&lock);

  num_writers++;
  while ((active_writer) || (num_readers > 0)) {
    pthread_cond_wait(&all_clear,&lock);
  }
  active_writer = true;
  pthread_mutex_unlock(&lock);
}

void RW_Lock::Writer_Unlock(void)
{
  pthread_mutex_lock(&lock);

  active_writer = false;
  num_writers--;
  if (num_writers == 0) {
    pthread_cond_broadcast(&no_writers);  // wake readers
  } else {
    pthread_cond_signal(&all_clear);     // wake another writer
  }

  pthread_mutex_unlock(&lock);
}

