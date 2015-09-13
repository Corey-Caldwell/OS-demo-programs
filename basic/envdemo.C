/*
 * Demonstrate getenv() and some environment variables.
 *
 * Bryan Clair
 * 2006
 */
#include <iostream>
#include <stdlib.h>
using namespace std;

main() {
  cout << "USER: " << getenv("USER") << endl;
  cout << "SHELL: " << getenv("SHELL") << endl;
  cout << "HOME: " << getenv("HOME") << endl;
}
