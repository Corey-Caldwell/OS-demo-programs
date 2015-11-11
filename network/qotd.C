/*
 * qotd
 *   usage: qotd hostname
 *
 *   Connect to a quote-of-the-day server on port 17, running QOTD protocol.
 *   The server will send an ascii text message of no more than 512 characters.
 *   See
 *     http://www.faqs.org/rfcs/rfc865.html for details
 *
 *  Bryan Clair
 *  2006-13
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

#define BUFSIZE 512

void fail(const char *str) { perror(str); exit(1); }

int main(int argc, char *argv[])
{
  // check arguments
  if (argc != 2) {
    cerr << "usage: qotd hostname" << endl;
    exit(1);
  }

  // look up host information - specify hostname and qotd service
  int err;
  struct addrinfo *host;
  err = getaddrinfo(argv[1],"qotd",NULL,&host);
  if (err) {
    cerr << argv[1] << " : " << gai_strerror(err) << endl;
    exit(err);
  }

  // create socket
  int sock = socket(host->ai_family,SOCK_STREAM,0);
  if (sock < 0) fail("socket");

  // connect to server
  if (connect(sock,host->ai_addr,host->ai_addrlen)) fail("connect");

  // clean up - free the memory allocated by getaddrinfo
  freeaddrinfo(host);

  // Promote the socket to a FILE stream for input
  FILE *serv_stream = fdopen(sock,"r");
  if (serv_stream == NULL) fail("fdopen");

  char buf[BUFSIZE];
  while (fgets(buf,BUFSIZE,serv_stream) != NULL) {
    fputs(buf,stdout);      // note: fgets leaves a newline at end of string
  }

  fputc('\n',stdout);  // final newline in case not supplied by server

  fclose(serv_stream);
}
