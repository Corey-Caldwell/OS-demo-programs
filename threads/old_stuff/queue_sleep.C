/*
 * SleepQueue class
 *
 *    Implements a queue where the dequeue function sleeps until
 *    it can return a valid object.
 */

class SleepQueue {
public:
  SleepQueue();
  void enqueue(Object *it);
  Object *dequeue();
private:
  Object *first;
  Object *last;
  pthread_mutex_t lock;
  pthread_cond_t notempty;
};

SleepQueue::SleepQueue()
{
  first = NULL;
  last = NULL;

  pthread_mutex_init(&lock,NULL);
  pthread_cond_init(&notempty,NULL);
}

void SleepQueue::enqueue(Object *it)
{
  it->next = NULL;

  pthread_mutex_lock(&lock);

  if (first == NULL) {
    first = last = it;
    pthread_cond_broadcast(&notempty);
  } else {
    last->next = it;
    last = it;
  }

  pthread_mutex_unlock(&lock);
}

Object *SleepQueue::dequeue()
{
  Object *who;

  pthread_mutex_lock(&lock);

  while (first == NULL) {
    pthread_cond_wait(&notempty,&lock);
  }

  who = first;
  first = first->next;

  pthread_mutex_unlock(&lock);

  return who;
}
