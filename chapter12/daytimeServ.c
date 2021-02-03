#include "ch.h"
#include "daytime.h"
#include "mysocket.c"
int main(int argc, char **argv, char **env){
	int listenfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buf[1024];
	time_t ticks;
	listenfd = make_socket(SOCK_STREAM, dayTimeServPort_int);
	listen(listenfd, 10);
	while(1){
			len = sizeof(cliaddr);
			connfd = accept(listenfd,(struct sockaddr *)&cliaddr, &len);
			printf("connect from %s, port %d\n",
							inet_ntoa((struct in_addr)cliaddr.sin_addr),
							ntohs(cliaddr.sin_port));
			ticks = time(NULL);
			memset(buf,0, sizeof(buf));
			sprintf(buf, "%.24s\r\n", ctime(&ticks));
			write(connfd, buf, strlen(buf));
			close(connfd);

	}
	return 0;
}
