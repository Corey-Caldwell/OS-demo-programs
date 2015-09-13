/*
 * iecho
 *    Accept a connection from one client on specified port.
 *    Echo all data back to client.
 *
 * Bryan Clair
 * 2006
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
using namespace std;

#define BUFSIZE 512

void fail(const char *str) { perror(str); exit(1); }

//
// main
//    Set up a listening socket and accept one connection.
//
int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr,"usage: iecho port\n");
    exit(1);
  }

  // create an address structure a passive socket at the requested port
  int err;
  struct addrinfo *host;
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_flags = AI_PASSIVE;
  err = getaddrinfo(NULL,argv[1],&hints,&host);
  if (err) {
    cerr << argv[1] << " : " << gai_strerror(err) << endl;
    exit(err);
  }

  // create socket
  int serv_sock = socket(host->ai_family,SOCK_STREAM,0);
  if (serv_sock < 0) fail("socket");

  // bind public socket to listening address
  if (bind(serv_sock,host->ai_addr,host->ai_addrlen)) fail("bind");

  // set the socket to listen (allow 5 pending connections)
  if (listen(serv_sock,5)) fail("listen");

  // clean up - free the memory allocated by getaddrinfo
  freeaddrinfo(host);

  cout << "Waiting for a connection on port " << argv[1] << endl;

  // accept one incoming connection
  int new_sock = accept(serv_sock,NULL,NULL);
  if (new_sock < 0) fail("accept");

  cout << "Accepted new connection on fdesc " << new_sock << endl;

  // promote the socket to a pair of FILE streams for input/output
  FILE *client_in = fdopen(new_sock,"r");
  FILE *client_out = fdopen(new_sock,"w");
  if ((client_in == NULL) || (client_out == NULL)) fail("fdopen");
  setlinebuf(client_out);
  
  // copy input to output, one line at a time
  char buf[BUFSIZE];
  while (fgets(buf,BUFSIZE,client_in) != NULL) {
    if (fputs(buf,client_out) == EOF) break;  // detect client disconnect
  }

  fclose(client_in);
  fclose(client_out);

  cout << "Connection closed" << endl;
}
