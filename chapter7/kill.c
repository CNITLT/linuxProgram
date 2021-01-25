#include "ch.h"
volatile sig_atomic_t usr_interrupt = 0;
void sig_usr(int sig){
	usr_interrupt = 1;
}

void child_function(void){
	printf("I'm child! My pid is %d\n",getpid());
	sleep(3);
	kill(getppid(), SIGUSR1);
	puts("Bye\n");
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv, char **env){
	pid_t child_id;
	signal(SIGUSR1,sig_usr);	
	child_id = fork();
	if(0 == child_id){
		child_function();
	}
	while(!usr_interrupt);
	puts("that's all");
	return 0;
}
