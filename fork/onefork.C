/*
 * onefork.C - fork once, print, exit.
 *
 *  Bryan Clair 2002
 */

#include <iostream>
#include <unistd.h>
using namespace std;

main()
{
  cout << "Ready...\n";
  fork();
  cout << "Done!\n";
}
