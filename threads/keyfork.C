/*
  keyfork.C

  fork() while a second thread is waiting on keyboard input.

  Bryan Clair
  2008-2015
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
  pthread_t tone, ttwo;

  /* make new threads */
  pthread_create(&tone,NULL,readline,NULL);
  pthread_create(&ttwo,NULL,readline,NULL);

  fork();

  sleep(30);
}  
