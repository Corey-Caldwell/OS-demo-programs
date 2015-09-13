//
// Try to solve the critical section problem by taking turns.
//
int turn = 0;

Thread0() {
  while(1) {
    // Entry
    while (turn == 1);  // spin until it's my turn

    Critical_Section();
    
    // Exit
    turn = 1;  // it's Thread1's turn next
    
    Remainder_Section();
  } 
}

Thread1() {
  while(1) {
    // Entry
    while (turn == 0);  // spin until it's my turn

    Critical_Section();
    
    // Exit
    turn = 0;  // it's Thread0's turn next
    
    Remainder_Section();
  } 
}
