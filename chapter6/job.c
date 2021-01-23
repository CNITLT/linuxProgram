#include "ch.h"
//验证管理连接的进程组id和用;连接的进程组id的区别:
int main(int argc, char **argv, char **env){
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	scanf("%s",buf);
	//printf中间打印的不能有空格，不然下一个scanf读取的不全
	printf("pid:%d,pgid:%d,buf:%s\n", getpid(),getpgrp(),buf);
	return 0;
}
