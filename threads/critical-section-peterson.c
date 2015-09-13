//
// Peterson's solution to the critical section problem
//
bool interested0 = false;
bool interested1 = false;
int turn;

Thread0() {
  while(1) {
    // Entry
    interested0 = true;
    turn = 1;
    // spin while Thread1 is interested and has the turn.
    while (turn == 1 && interested1); 

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
    turn = 0;
    // spin while Thread1 is interested and has the turn.
    while (turn == 0 && interested0); 

    Critical_Section();
    
    // Exit
    interested1 = false;
    
    Remainder_Section();
  } 
}
