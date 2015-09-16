/*
 * sig_demo.C
 *   Ignore ^C, catch and respond to ^| and USR1 signal.
 *
 * Bryan Clair, 2002-2015
 */

#include <iostream>
#include <unistd.h>
#include <signal.h>

using namespace std;

//
// handle_signal
//   Called asynchronously when signals are received.
//   It's not generally safe to use cout in a signal handler.
//
//   int the_sig is the type of signal received.
//
void handle_signal(int the_sig)
{
  switch(the_sig) {
  case SIGQUIT:
    cout << "Caught SIGQUIT.\n";
    break;
  case SIGUSR1:
    cout << "Caught SIGUSR1.\n";
    break;
  }
}

main()
{
  // set ^C to be ignored
  signal(SIGINT,SIG_IGN);

  // set handler to catch ^| and USR1 signal
  signal(SIGQUIT,handle_signal);
  signal(SIGUSR1,handle_signal);

  // count for a while
  int i, timeleft;
  for (i=0; ;i++) {
    cout << i << endl;
    timeleft = sleep(1);
    if (timeleft != 0)
      cout << "woke with " << timeleft << " second left" << endl;
  }
}
