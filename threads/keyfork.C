/*
  keyfork.C

  fork() while a second thread is waiting on keyboard input.

  Bryan Clair
  Sep. 2008
*/

#include <iostream>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void *readline(void *v)
{
  char line[256];
  cout << "Type: " << endl;
  
  if (!cin.getline(line,255)) {
    cerr << "error!" << endl;
  } else {
    cout << line << endl;
  }

  cout << "exiting" << endl;
}

main()
{

  /* make new thread */
  pthread_t id;
  pthread_create(&id,NULL,readline,NULL);

  sleep(1);
  fork();

  pthread_exit(NULL);
}  
