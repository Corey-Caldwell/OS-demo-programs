/*
 * time37
 *   usage: time37 hostname
 *
 *   Connect to a time-of-day server on port 37, running "time" protocol.
 *   The server will send a 4-byte time in seconds since January 1, 1900.
 *   See
 *      http://www.nist.gov/pml/div688/grp40/its.cfm
 *   for details and server names.
 *
 * Bryan Clair
 * 2006-13
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
using namespace std;

void fail(const char *str) { perror(str); exit(1); }

main(int argc, char *argv[])
{
  // check arguments
  if (argc != 2) {
    cerr << "usage: time37 hostname" << endl;
    exit(1);
  }
  
  // look up host information - specify hostname and "time" service
  int err;
  struct addrinfo *host;
  err = getaddrinfo(argv[1],"time",NULL,&host);
  if (err) {
    cerr << argv[1] << " : " << gai_strerror(err) << endl;
    exit(err);
  }

  // create socket
  int sock = socket(host->ai_family,SOCK_STREAM,0);
  if (sock < 0) fail("socket");

  // connect to time server
  if (connect(sock,host->ai_addr,host->ai_addrlen)) fail("connect");

  // clean up - free the memory allocated by getaddrinfo
  freeaddrinfo(host);

  // tsecs will recieve the time from the server
  //   ..it's a 32-bit unsigned integer.
  uint32_t tsecs = 0;

  // read 4 bytes from socket
  int n = read(sock,&tsecs,4);

  if (n == -1) fail("read");  // read returned error
  if (n != 4) {
    // read may return less than 4 bytes, or the server may
    // be broken.  The right thing to do would be to read
    // more bytes until 4 have arrived.  Here, we do the
    // easy thing - quit and make the user try again.
    cerr << "try again" << endl;
    exit(1);
  }

  // convert from network byte order to host byte order.
  // (one might be big-endian, one might be little-endian)
  tsecs = ntohl(tsecs);

  // report time
  cout << tsecs << endl;

  close(sock);
}
