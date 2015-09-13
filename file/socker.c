/*
 * socker.c
 *   Create a file "socketfile" in the current directory of type socket.
 */
 
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

main()
{
  int s = socket(PF_UNIX,SOCK_STREAM,0);

  struct sockaddr_un name;
  name.sun_family = AF_UNIX;
  strcpy(name.sun_path,"socketfile");
  bind(s,(struct sockaddr *)&name,sizeof(name));
}

