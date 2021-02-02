#include "ch.h"
#include "showHostent.h"
int main(int argc, char **argv, char **env){
	if(argc < 2){
		err_exit("no host\n");
	}
	int i = 1;
	for(;i<argc;i++){
		struct hostent *host = gethostbyname(argv[i]);
		showHostent(host);
	}
	return 0;
}
