//
// Try to solve the critical section problem with a shared lock variable.
//
bool lock = false;

Thread0() {
  while(1) {
    // Entry
    while (lock);  // spin until lock is false
    lock = true;
    
    Critical_Section();
    
    // Exit
    lock = false;
    
    Remainder_Section();
  } 
}

Thread1() {
  while(1) {
    // Entry
    while (lock);  // spin until lock is false
    lock = true;
    
    Critical_Section();
    
    // Exit
    lock = false;
    
    Remainder_Section();
  } 
}
