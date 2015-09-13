/*
 * ilisten2
 *    Accept connections from multiple clients on specified port.
 *    Echo all data received from the clients to stdout.
 *
 * Bryan Clair
 * 2004-13
 */
#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>
#include <string.h>
using namespace std;

#define BUFSIZE 512

void fail(const char *str) { perror(str); exit(1); }

//
// serve_one_client
//   Argument is pointer to malloc'ed integer file descriptor of client socket
//   Handle input from one connected client
//
void *serve_one_client(void *v)
{
  int sock = *(int *)v;
  free(v);

  // promote client's socket to a stream
  FILE *myclient = fdopen(sock,"r");
  if (myclient == NULL) {
    perror("fdopen");
    pthread_exit(0);
  }

  char buf[BUFSIZE];

  // echo client data to stdout one line at a time
  while (fgets(buf,BUFSIZE,myclient) != NULL) {
    fputs(buf,stdout);
  }

  cout << "Connection closed on fdesc " << sock << endl;

  fclose(myclient);
  pthread_exit(0);
}

//
// main
//   Receive connections and create threads to service them.
//
int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr,"usage: ilisten2 port\n");
    exit(1);
  }

  // create an address structure for a passive socket at the requested port
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

  cout << "Waiting for connections on port " << argv[1] << endl;

  int *new_sock;
  pthread_t new_thread;

  while (true) {
    // space for the integer value of the socket (so it can be passed to the
    // serve_one_client() thread routine as an argument)
    new_sock = (int *)malloc(sizeof(int));

    // accept one incoming connection
    *new_sock = accept(serv_sock,NULL,NULL);
    if (*new_sock < 0) fail("accept");

    cout << "Accepted new connection on fdesc " << *new_sock << endl;

    // create & detach a thread to serve the new client
    pthread_create(&new_thread,NULL,serve_one_client,new_sock);
    pthread_detach(new_thread);
  }
}
