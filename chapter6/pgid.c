#include "ch.h"

int main(int argc, char **argv, char **env){
	printf("parent pid:%d, pgid:%d\n",getpid(), getpgrp());
	pid_t pid;
	pid = fork();

	if(pid < 0){
		err_exit("fork failed\n");
	}
	if(0 == pid){

		printf("setpgid before child pid:%d, pgid:%d\n",getpid(), getpgrp());
		//setpgid(0,0);
		//printf("setpgid after child pid:%d, pgid:%d\n",getpid(), getpgrp());
		sleep(10);
		printf("parent setpgig after child pid:%d, pgid:%d\n",getpid(), getpgrp());
	}
	sleep(3);
	setpgid(pid, 0);
	return 0;
}
