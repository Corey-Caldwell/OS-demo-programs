/*
 * rwlock.h
 *    defines class RW_Lock
 *    readers/writers lock that allows multiple readers or one writer.
 *
 * If writers are waiting to work, no new readers are allowed to get
 * the lock.
 *
 * Bryan Clair
 * 2003
 *
 */
#ifndef RWLOCK_H
#define RWLOCK_H

#include <pthread.h>

class RW_Lock {
public:
  RW_Lock(void);
  void Reader_Lock(void);
  void Reader_Unlock(void);
  void Writer_Lock(void);
  void Writer_Unlock(void);

private:
  pthread_mutex_t lock;
  pthread_cond_t no_writers;
  pthread_cond_t all_clear;
  
  bool active_writer;  // true if a writer holds the RW lock.
  int num_writers; // counts number of active/waiting writers.
  int num_readers; // counts number of active readers.
};

#endif
