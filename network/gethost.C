/*
 * gethost
 *   Convert a DNS host name into an internet address
 * 
 * Bryan Clair
 * 2006-13
 */

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
  // check arguments
  if (argc != 2) {
    cerr << "usage: gethost hostname" << endl;
    exit(1);
  }

  // look up host information
  int err;
  struct addrinfo *host;
  err = getaddrinfo(argv[1],NULL,NULL,&host);
  if (err) {
    cerr << argv[1] << " : " << gai_strerror(err) << endl;
    exit(err);
  }
  
  // get the numeric name
  char numeric_name[NI_MAXHOST];
  err = getnameinfo(host->ai_addr,host->ai_addrlen,
		    numeric_name,NI_MAXHOST,
		    NULL,0,NI_NUMERICHOST);
  if (err) {
    cerr << argv[1] << " : " << gai_strerror(err) << endl;
    exit(err);
  }

  cout << numeric_name << endl;

  // clean up - free the memory allocated by getaddrinfo
  freeaddrinfo(host);
}


