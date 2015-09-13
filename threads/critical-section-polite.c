//
// Try to solve the critical section problem with politeness:  you go first.
//
bool interested0 = false;
bool interested1 = false;

Thread0() {
  while(1) {
    // Entry
    interested0 = true;
    while (interested1);  // spin until Thread1 is no longer interested

    Critical_Section();
    
    // Exit
    interested0 = false;
    
    Remainder_Section();
  } 
}

Thread1() {
  while(1) {
    // Entry
    interested1 = true;
    while (interested0);  // spin until Thread0 is no longer interested

    Critical_Section();
    
    // Exit
    interested1 = false;
    
    Remainder_Section();
  } 
}
