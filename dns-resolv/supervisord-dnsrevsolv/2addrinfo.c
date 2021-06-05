#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {

const char *arg="AlarmSystemLight.local";
const char *port="49712";
struct addrinfo hints;

  struct addrinfo *res;

  memset(&hints, 0, sizeof(hints));
  /* set-up hints structure */
hints.ai_family = AF_INET;
hints.ai_socktype = SOCK_STREAM;
  int error = getaddrinfo(arg, port, &hints, &res);
  if (error) {
    perror(gai_strerror(error));
    return 1;
  } else {
	struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
	char ipAddress[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(ipv4->sin_addr), ipAddress, INET_ADDRSTRLEN);

	struct timespec before;
     clock_gettime(CLOCK_MONOTONIC,&before);
	printf("The IP address of alarmsystemlight.local is: %s sec=%d nsec=%ld\n", ipAddress,before.tv_sec,before.tv_nsec);

	int fd = -1;
	if ( (fd=socket(AF_INET, SOCK_STREAM,0)) == -1 )
		{
			perror("Socke creation fialure:");
			exit(100);
		}

    /*
     *    struct sockaddr_in servaddr;
     *    // assign IP, PORT 
     *servaddr.sin_family = AF_INET; 
     *servaddr.sin_addr.s_addr = htonl(ipAddress); 
     *servaddr.sin_port = htons(77); 
     */

	if( bind(fd, res->ai_addr,
                res->ai_addrlen) !=0 ){
		perror("bind failure");
		exit(200);
	}

	printf("Bind success.\n");
	sleep(300);
  }
}
