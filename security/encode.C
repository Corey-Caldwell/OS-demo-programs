/*
 * encode
 *
 *  usage: encode salt
 *    Hashes each line of stdin using the crypt(3) function and the given salt.
 *    Only the first two letters of salt are significant.
 *
 * Bryan Clair, 2008.
 */
#define _XOPEN_SOURCE
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <crypt.h>

using namespace std;

main(int argc, char *argv[])
{
  if (argc != 2) {
    cerr << "usage: " << argv[0] << " salt" << endl;
    exit(1);
  }
  char *salt = argv[1];

  struct crypt_data cd;
  cd.initialized = 0;
  char key[128];

  while (cin.getline(key,128)) {
    cout << crypt_r(key,salt,&cd) << endl;
  }
}
