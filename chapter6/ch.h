#ifndef _CH_H_
#define _CH_H_
#include <stdio.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/ipc.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <sys/msg.h>
#include <termios.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/un.h>
#include <signal.h>
#include <netinet/in.h>
#define err_exit(mesg){printf(mesg);exit(1);}

#endif 
