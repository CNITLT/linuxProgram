#include "ch.h"

int main(int argc, char **argv, char **env){
	char c, *shm, *s;
	int shmid;
	if((shmid = shmget(0x1111, 1024, 0666))<0){
		perror(NULL);
		err_exit("shmget failed\n");
	}
	if((shm = shmat(shmid, NULL, 0)) == (char *)-1){
		perror(NULL);
		err_exit("shmat failed\n");
	}
	s = shm;
	printf("%s\n", s);
	return 0;
}
