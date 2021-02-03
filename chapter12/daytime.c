#include "ch.h"
#include "mysocket.h"
#include "daytime.h"
int main(int argc, char **argv, char **env){
	int sockfd, n;
	char recvbuf[1024], *host;
	struct sockaddr_in servaddr;
	if(argc < 2){
		host = NULL;
	}
	else{
		host = argv[1];
	}
	sockfd = socket_connect(host, dayTimeServPort);
	printf("test\n");
	while((n = read(sockfd, recvbuf,sizeof(recvbuf))) > 0){
			recvbuf[n] = 0;
			printf("%s\n", recvbuf);
	}
	if(n < 0){
		err_exit("read error\n");
	}
	return 0;
}
