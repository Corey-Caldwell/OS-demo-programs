/*
 * Queue class
 *
 *   Implements a queue for single threaded use.
 *   If dequeue is called for an empty queue, it must return NULL.
 */

class Queue {
public:
  Queue();
  void enqueue(Object *it);
  Object *dequeue();
private:
  Object *first;
  Object *last;
};

Queue::Queue()
{
  first = NULL;
  last = NULL;
}

void Queue::enqueue(Object *it)
{
  it->next = NULL;

  if (first == NULL) {
    first = last = it;
  } else {
    last->next = it;
    last = it;
  }
}

Object *Queue::dequeue()
{
  Object *who;

  who = first;
  if (first != NULL) first = first->next;

  return who;
}
