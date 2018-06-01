#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define PORT "9034" // the port client will be connecting to
#define BUFSIZE 1024


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int sendall(int sockfd, char *buf, int *len)
{
  int total = 0;
  int n = 0;
  while(total < *len) {
    n = send(sockfd, buf+total, *len-total, 0);
    if(n == -1) { break; }
    total += n;
  }
  *len = total;
  return n == -1 ? -1 : 0;
}

int main(int argc, char *argv[])
{
  int rv, sockfd, i, read, j, ret;
  int fdmax = STDIN_FILENO;
  fd_set master;
  fd_set read_fds;
  char *ln;
  size_t lnsize;
  struct addrinfo hints, *servinfo, *p;
  char buf[BUFSIZE];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  }

  // loop through all the results and connect to the first we can
  for(p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype,
                         p->ai_protocol)) == -1) {
      /* perror("client: socket"); */
      continue;
    }

    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      /* perror("client: connect"); */
      close(sockfd);
      continue;
    }

    break;
  }

  if (p == NULL) {
    fprintf(stderr, "client: failed to connect\n");
    return 2;
  }

  fdmax = fdmax < sockfd ? sockfd : fdmax;

  FD_ZERO(&master);
  FD_SET(STDIN_FILENO, &master);
  FD_SET(sockfd, &master);

  for(;;) {
    read_fds = master;
    if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
      perror("select");
      exit(4);
    }

    for(i=0; i<=fdmax; i++) {
      if(FD_ISSET(i, &read_fds)) {
        if(i == STDIN_FILENO) {
          ln = NULL;
          lnsize = 0;
          read = getline(&ln, &lnsize, stdin);
          if(read == -1) {
            perror("getline");
            exit(1);
          }
          if((ret = sendall(sockfd, ln, (int *)&lnsize)) == -1) {
            perror("send");
            exit(1);
          }
        } else {
          if((read = recv(i, buf, sizeof(buf)-1, 0)) <= 0) {
            if(read == 0) {
              printf("selectserver: socket %d hung up\n", i);
              exit(1);
            } else {
              perror("recv");
              exit(1);
            }
          } else {
            buf[read] = '\0';
            printf("%s\n", buf);
          }
        }
      }
    }
  }
}
