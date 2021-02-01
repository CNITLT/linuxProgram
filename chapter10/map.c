#include "ch.h"


int main(int argc, char **argv, char **env){
	int fd = open("maptest.txt", O_CREAT | O_RDWR, 0644);
	int page_size = sysconf(_SC_PAGE_SIZE);
	lseek(fd,page_size,SEEK_SET);
	char *addr = mmap(0, page_size,PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
	printf("%c", addr[0]);
	scanf("%s",addr);

	return 0;
}
