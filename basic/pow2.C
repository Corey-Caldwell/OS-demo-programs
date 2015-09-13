/*
 * pow2.C
 *   Raise a number to a power (allows floating point powers)
 *   usage: pow2 base exponent
 *
 *   Bryan Clair 2002-2015
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
using namespace std;

main(int argc, char *argv[])
{
  if (argc != 3) {
    cerr << "usage: " << argv[0] << " base exponent\n";
    exit(1);
  }
  
  double x = atof(argv[1]);
  double y = atof(argv[2]);
  
  errno = 0;          // clear errno
  double answer = pow(x,y);  // pow will set errno if problems occur
  if (errno != 0) {
    perror(argv[0]);  // perror prints a message appropriate to errno
    exit(errno);      // might as well return a useful code
  }

  cout << answer << endl;
}
