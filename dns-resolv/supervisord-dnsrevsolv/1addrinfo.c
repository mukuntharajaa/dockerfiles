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

int main() {

const char *arg="relimesg.local";
const char *port="77";
struct addrinfo hints;

/*hints.ai_flags = AI_PASSIVE;*/

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
	printf("The IP address of relimesg.local isssss: %s sec=%d nsec=%ld\n", ipAddress,before.tv_sec,before.tv_nsec);


	int fd = -1;
	if ( (fd=socket(AF_INET, SOCK_STREAM,0)) == -1 )
		{
			perror("Socke creation fialure:");
			exit(100);
		}
	printf("socketsuccess.\n");

	// assign IP, PORT 
    /*
     *servaddr.sin_family = AF_INET; 
     *servaddr.sin_addr.s_addr = htonl(ipAddress); 
     *servaddr.sin_port = htons(59712); 
     */

	if( bind(fd, res->ai_addr,
                res->ai_addrlen) !=0 ){
		printf("bind failure %s\n",strerror(errno));
		perror("bind failure");
		exit(200);
	}

	printf("Bind success.\n");

	sleep(300);

  }
}
