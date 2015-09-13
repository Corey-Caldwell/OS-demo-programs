/*
 * sem_system.c
 *
 *   Psuedocode example of how an operating
 *   system might implement semaphores using
 *   low-level mutex
 */

struct sem_t {
  spinlock mu;
  int val;
  thread *queue;
}

/*
 * down
 *
 *   If semaphore value is positive, decrement it.
 *   Otherwise, wait.
 *   
 */

down(sem_t &sem) {
  while (1) {
    disable_interrupts();
    acquire_spinlock(mu);

    if (sem->val > 0) {
      // Semaphore was available
      sem->val--;
      release_spinlock(mu);
      enable_interrupts();
      return;
    } 
    else {
      // Semaphore in use - go to sleep
      this_thread->state = WAITING;
      enqueue(queue,this_thread);
      
      release_spinlock(mu);
      enable_interrupts();
      schedule();  // pick a READY thread to run
      // when schedule returns, this thread will be RUNNING
    }
  } // repeat
}

/*
 * up
 *
 *   Increment semaphore value.
 *   If other threads are waiting for the semaphore,
 *   wake one up.
 */

up(sem_t &sem) {

  disable_interrupts();
  acquire_spinlock(mu);

  sem->val++;

  if (not_empty(queue)) {
    // threads are waiting - wake one up
    
    other_thread = dequeue(queue);
    other_thread->state = READY;
    add_to_ready_queue(other_thread);
  }

  release_spinlock(mu);
  enable_interrupts();
}
