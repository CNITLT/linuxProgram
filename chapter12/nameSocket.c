#include "ch.h"

int main(int argc, char **argv, char **env){
	printf("sockaddr_un sizeof :%d\n", sizeof(struct sockaddr_un));
	int socket_fd = socket(AF_UNIX, SOCK_STREAM,0);
	if(socket_fd < 0){
		err_exit("socket failed\n\n");
	}
	struct sockaddr_un name;
	name.sun_family = AF_UNIX;
	strcpy(name.sun_path, "name.sock");
	if(-1 == bind(socket_fd,(struct sockaddr *)&name, sizeof(name))){
		perror(NULL);
		err_exit("bind failed\n");
	}
	return 0;
}
