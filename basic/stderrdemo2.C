/*
 * stderrdemo2.C
 *
 * In C++, cerr and cout intermingle.
 *
 *   Bryan Clair 2008
 */

#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
  cerr << "tic ";

  cout << "ping ";

  cerr << "tac ";

  cout << "pong ";
  
  sleep(1);

  cerr << "toe " << endl;

  cout << endl;
}
