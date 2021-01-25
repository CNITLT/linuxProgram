#include "ch.h"

int main(int argc, char **argv, char **env){
	int i = 0;
	char buf[1024];

	for(;i <NSIG; i++){
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "i:%d ",i);
		psignal(i, buf);
	}
	return 0;
}
