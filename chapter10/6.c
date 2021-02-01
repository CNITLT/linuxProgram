#include "ch.h"
int input_timeout(int filedes, unsigned int seconds){
	fd_set set;
	struct timeval timeout;
	int n;
	char buf[1024];
	FD_ZERO(&set);
	FD_SET(filedes, &set);
	timeout.tv_sec = seconds;
	timeout.tv_usec = 0;
again:
	if((n = select(FD_SETSIZE, &set, NULL,NULL, &timeout)) < 0){
		if(errno == EINTR){
			goto again;
		}		
	}
	else if(n > 0){
		n = read(filedes,buf,sizeof(buf));
		printf("read data:%s \n", buf);
	}
	else{
		printf("timeout for select\n");
	}
	return n;
}
int main(int argc, char **argv, char **env){
	fprintf(stderr, "select returned %d.\n",input_timeout(STDIN_FILENO,5));
	return 0;
}
