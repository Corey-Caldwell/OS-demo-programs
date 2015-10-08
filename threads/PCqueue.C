//
// Producer-Consumer queue.
// Unbounded queue, consumer will sleep until there is an object to consume.
// Templated version - Bryan Clair 2015
//
#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>

template<class Object>
class PCqueue {
public:
  PCqueue();
  void enqueue(Object);
  Object dequeue();
private:
  std::queue<Object> q;
  pthread_mutex_t lock; // protects q
  sem_t Qsize;
};

template<class Object>
PCqueue<Object>::PCqueue()
{
  pthread_mutex_init(&lock,NULL);
  sem_init(&Qsize,0,0);
}

// Add an Object to the queue
template<class Object>
void PCqueue<Object>::enqueue(Object it)
{
  pthread_mutex_lock(&lock);

  q.push(it);

  pthread_mutex_unlock(&lock);

  sem_post(&Qsize);
}

// Sleep until there is an Object on the queue, then return it.
template<class Object>
Object PCqueue<Object>::dequeue()
{
  Object it;

  sem_wait(&Qsize);

  pthread_mutex_lock(&lock);

  assert(!q.empty());
  it = q.front();
  q.pop();

  pthread_mutex_unlock(&lock);

  return it;
}

