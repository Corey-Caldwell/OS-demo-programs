/*
 * pow.C
 *   Raise a number to a power
 *   usage: pow base exponent
 *
 *   Bryan Clair 2002-2015
 */

#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
  if (argc != 3) {
    cerr << "usage: " << argv[0] << " base exponent\n";
    exit(1);
  }

  double b = atof(argv[1]);

  int n = atoi(argv[2]);
  if (n < 0) {
    cerr << "exponent must be positive\n";
    exit(1);
  }

  double answer = 1;
  for (int i = 0; i < n; i++)
    answer *= b;

  cout << answer << endl;
}
