#include "ch.h"
#include "showHostent.h"
int main(int argc, char **argv, char **env){
	struct hostent * hostPtr = gethostent();
	while(hostPtr){
		showHostent(hostPtr);
		hostPtr = gethostent();
	}
	return 0;
}
