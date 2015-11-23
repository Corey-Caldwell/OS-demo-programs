/*
 * ispeak
 *   usage: ispeak hostname port
 *
 *   Create an internet socket and connect to specified port at hostname.
 *   Then copy from stdin to the socket.
 *
 *  Bryan Clair
 *  2006
 */
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
using namespace std;

#define BUFSIZE 512

void sigIgnoreHandler(int sig_num)
{
  signal(SIGPIPE,sigIgnoreHandler);
}

void fail(const char *str) { perror(str); exit(1); }

//
// main
//   Open a connection and send data from stdin to the socket
//
int main(int argc, char *argv[])
{
  // check arguments
  if (argc != 3) {
    cerr << "usage: ispeak hostname port" << endl;
    exit(1);
  }
  
  signal(SIGPIPE,sigIgnoreHandler);

  // look up host information - specify hostname and port service
  int err;
  struct addrinfo *host;
  err = getaddrinfo(argv[1],argv[2],NULL,&host);
  if (err) {
    cerr << argv[1] << " : " << gai_strerror(err) << endl;
    exit(err);
  }

  // create socket
  int sock = socket(host->ai_family,SOCK_STREAM,0);
  if (sock < 0) fail("socket");

  // connect to host
  if (connect(sock,host->ai_addr,host->ai_addrlen)) fail("connect");

  // clean up - free the memory allocated by getaddrinfo
  freeaddrinfo(host);

  // promote the socket to a FILE stream for output
  FILE *serv_stream = fdopen(sock,"w");
  if (serv_stream == NULL) fail("fdopen");
  setlinebuf(serv_stream);  // hint that writing should buffer by line

  // copy stdin to server, one line at a time
  char buf[BUFSIZE];
  while (fgets(buf,BUFSIZE,stdin) != NULL) {
    if (fputs(buf,serv_stream) == EOF) break;  // detect server disconnect
  }

  fclose(serv_stream);

  cout << "Connection closed" << endl;
}
  
      
