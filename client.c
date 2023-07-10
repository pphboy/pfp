#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

void error_exit(char *msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[]) {
  char* server = "127.0.0.1";
  char buf[1024];
  int port = 8090,addrlen = -1;
  int sockfd = -1;
  struct sockaddr_in addr;

  sockfd = socket(PF_INET, SOCK_STREAM, 0);
    
  addrlen = sizeof addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(server);

  if(connect(sockfd, (struct sockaddr*)&addr, sizeof addr) == -1) {
    error_exit("Connection");
  }

  strcpy((char*)&buf, "MSG: hello");
  
  write(sockfd,&buf, strlen(buf));
  

  close(sockfd);
    
  return 0;
}
