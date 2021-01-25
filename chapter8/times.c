#include "ch.h"

int main(int argc, char **argv, char **env){
	clock_t res = times(NULL);
	printf("res:%ld res/TICK:%ld",res, res/sysconf(_SC_CLK_TCK));
	return 0;
}
