/*
 * SleepQueue class
 *
 *    Implements a queue where the dequeue function sleeps until
 *    it can return a valid object.
 */
#include <queue>
#include <pthread.h>

using namespace std;

class Object;

class SleepQueue {
public:
  SleepQueue();
  void enqueue(Object *it);
  Object *dequeue();
private:
  queue<Object *> q;
  pthread_mutex_t lock;
  pthread_cond_t notempty;
};

SleepQueue::SleepQueue()
{
  pthread_mutex_init(&lock,NULL);
  pthread_cond_init(&notempty,NULL);
}

void SleepQueue::enqueue(Object *it)
{
  pthread_mutex_lock(&lock);

  if (q.empty()) {
    pthread_cond_broadcast(&notempty);
  }
  q.push(it);

  pthread_mutex_unlock(&lock);
}

Object *SleepQueue::dequeue()
{
  Object *it;

  pthread_mutex_lock(&lock);

  while (q.empty()) {
    pthread_cond_wait(&notempty,&lock);
  }
  it = q.front();
  q.pop();

  pthread_mutex_unlock(&lock);

  return it;
}
