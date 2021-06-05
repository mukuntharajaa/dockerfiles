#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if ( argc <= 2 )
    {
        printf("Not enough arguments, exiting\n");
        printf("Ex: %s service1.local 77\n",argv[0]);
        exit(999);
    }
    const char *arg = argv[1];
    const char *port = argv[2];

/*
 *const char *arg="service1.local";
 *const char *port="77";
 */
struct addrinfo hints;
struct addrinfo *res;

  memset(&hints, 0, sizeof(hints));
  /* set-up hints structure */
hints.ai_family = AF_INET;
hints.ai_socktype = SOCK_STREAM;
  int error = getaddrinfo(arg, port, &hints, &res);
  if (error) {
    perror(gai_strerror(error));
    printf("getaddrinfo failure\n",strerror(errno));
    exit(500);
  } else {
	struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
	char ipAddress[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(ipv4->sin_addr), ipAddress, INET_ADDRSTRLEN);
	struct timespec before;
    clock_gettime(CLOCK_MONOTONIC,&before);
	printf("The IP address of service1.local is: %s sec=%d nsec=%ld\n", ipAddress,before.tv_sec,before.tv_nsec);


	int fd = -1;
	if ( (fd=socket(AF_INET, SOCK_STREAM,0)) == -1 )
		{
            printf("Socket creation failure : %s \n",strerror(errno));
			perror("Socke creation fialure:");
			exit(100);
		}
	printf("socket creation success.\n");

	if( bind(fd, res->ai_addr,
                res->ai_addrlen) !=0 ){
		printf("bind failure %s\n",strerror(errno));
		perror("bind failure");
		exit(200);
	}
	printf("Bind success. Going to sleep now for 300 seconds\n");
	sleep(300);
  }
}
