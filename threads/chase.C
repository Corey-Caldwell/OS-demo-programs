/*
 * chase
 *    A chase game.  User runs from menacing asterisk.
 * 
 * Bryan Clair 2002
 */

#include <iostream>
#include <pthread.h>
#include <curses.h>
#include <unistd.h>
using namespace std;

// Globals hold players current position
volatile int x_player, y_player;

// Forward declarations
void *player(void *);
void *chaser(void *);

//
// main
//   Set up screen, create player and chaser threads.
//
int main()
{
  // Initialize Curses
  initscr();  // init screen
  cbreak();   // cbreak mode - char at a time
  noecho();   // don't echo typed chars

  // Create player
  y_player = LINES/2;
  x_player = COLS/2;
  pthread_t player_thread;
  pthread_create(&player_thread,NULL,player,NULL);

  // Create chaser
  pthread_t chaser_thread;
  pthread_create(&chaser_thread,NULL,chaser,NULL);

  // Wait for player thread to exit
  pthread_join(player_thread,NULL);
  endwin();
}
    
//
// chaser
//    Procedure for chaser thread.  Moves toward the player.
//
void *chaser(void *unused)
{
  int x=0,y=0;

  while (1) {
    move(y,x);
    addch('*');
    refresh();
    usleep(250000);
    move(y,x);
    addch(' ');
    if (x < x_player) x++;
    if (x > x_player) x--;
    if (y < y_player) y++;
    if (y > y_player) y--;
  }
}

//
// player
//    Procedure for player thread.  Gets key input and moves in
//    that direction.
//
void *player(void *unused)
{
  int x = x_player, y = y_player;
  char key = 0;

  while (key != 'q') {
    move(y,x);
    addch('O');
    refresh();

    x_player = x; y_player = y;  // update globals

    key = getch();  // wait for keypress

    move(y,x);
    addch(' ');

    switch (key) {
    case 'j':
      if (--x < 0) x = 0;
      break;
    case 'l':
      if (++x == COLS) x = COLS-1;
      break;
    case 'i':
      if (--y < 0) y = 0;
      break;
    case 'k':
      if (++y == LINES) y = LINES-1;
      break;
    }
  }
}







