#include <iostream>
#include <unistd.h>
using namespace std;

main()
{
  fork();  cout << "hee " << endl;
  fork();  cout << "ha " << endl;
  fork();  cout << "ho " << endl;
}
