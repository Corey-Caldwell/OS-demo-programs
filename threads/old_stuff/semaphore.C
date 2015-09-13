//
// Semaphore class
//    Built out of mutexes and condition variables
//    (using the pthread library)
//

class Semaphore {
public:
  Semaphore(int value=1);  // default value is 1
  void Signal(void);
  void Wait(void);

private:
  int S;
  pthread_mutex_t lock;
  pthread_cond_t S_is_positive;
};

Semaphore::Semaphore(int value)
{
  pthread_mutex_init(&lock,NULL);
  pthread_cond_init(&S_is_positive,NULL);
  S = value;
}

void Semaphore::Signal(void)
{
  pthread_mutex_lock(&lock);

  S++;
  if (S > 0) pthread_cond_broadcast(&S_is_positive);

  pthread_mutex_unlock(&lock);
}

void Semaphore::Wait(void)
{
  pthread_mutex_lock(&lock);
  
  while (S <= 0)
    pthread_cond_wait (&S_is_positive, &lock);

  S--;
  
  pthread_mutex_unlock (&lock);
}

