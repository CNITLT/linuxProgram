#include "ch.h"
#define DATA1 "Fine,thanks"
#define DATA2 "Hello, how are you"
int main(int argc, char **argv, char **env){
	int sockets[2], child;
	char buf[1024];
	if(socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0){
		err_exit("socketpair error\n");
	}
	child = fork();
	if(child != 0){
		close(sockets[0]);
		if(read(sockets[1], buf, sizeof(buf)) < 0){
			err_exit("read failed\n");
		}
		printf("parent received request:%s\n",buf);
		if(write(sockets[1],DATA1, sizeof(DATA1))<0){
			err_exit("write failed\n");
		}
		close(sockets[1]);
	}
	else{	
		close(sockets[1]);
		if(write(sockets[0], DATA2, sizeof(DATA2)) < 0){
			err_exit("write failed\n");
		}
		if(read(sockets[0],buf, sizeof(buf))<0){
			err_exit("read failed\n");
		}
		printf("chiled received request:%s\n",buf);
		close(sockets[0]);
	}
	return 0;
}
