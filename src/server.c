#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT 8090

void error_exit(char *msg) {
  perror(msg);
  exit(1);
}

void handle_conn(int connfd);

int main(int argc, char * argv) {
  printf("Server Address: 127.0.0.1:%d\n",PORT);
  int sockfd,addr_len,connfd;
  char buf[1024];
  struct sockaddr_in addr;
  addr_len = sizeof(addr);

  if(( sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    error_exit("socket");
  }

  int reuse = 1;
  if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof reuse) == -1) {
    error_exit("setsockopt");
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(sockfd, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
    error_exit("Binding");
  }

  if(listen(sockfd, 10) == -1) {
    error_exit("Listen");
  }

  while(1) {
    connfd = accept(sockfd, (struct sockaddr*)&addr, (socklen_t*)& addr_len);
    if(connfd == -1) error_exit("Accept");

    handle_conn(connfd);
    // recv
  }

  return 0;
}

void handle_conn(int connfd) {
  char buf[1024];
  bzero(&buf,sizeof(buf));
  int len = 1024;

  printf("\nRECV:\n");
  
  len = recv(connfd, &buf, sizeof(buf), 0);
  printf("[%d]%s",len,buf);

  close(connfd);
}
